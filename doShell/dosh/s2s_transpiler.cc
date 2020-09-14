// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#include <doShell/dosh/s2s_transpiler.h>

namespace doShell {

// Constructor: init (resolve) command and arguments
S2sTranspiler::S2sTranspiler(int argc, const std::vector<std::string> &argv) {
  argc_ = argc;
  argv_ = argv;

  // ...
}

// Transpile given *.do.sh file to *.sh
bool S2sTranspiler::Compile() {
  if (argc_ <= 1) return CompileAllInPath();

  if (!LoadSource()) return false;

  InitPathSourceDirectory();
  InitPathFileCompiled();

  if (helper::File::FileExists(path_compiled_file_abs_))
    return helper::File::GetFileContents(path_compiled_file_abs_, &source_);

  ResolveImports();
  TranspileCommands();

  CleanupSource();
  helper::File::WriteToNewFile(path_compiled_file_abs_, source_);

  return true;
}

void S2sTranspiler::TranspileCommands() {
  bool contains_commands;

  int runs = 0;

  do {
    if ((contains_commands = SourceContainsCommands())) {
      transpileString::Transpile(&source_, is_linux_);
      transpileUrl::Transpile(&source_, is_linux_);
      transpileRandom::Transpile(&source_, is_linux_);
      transpileClipboard::Transpile(&source_, is_linux_);
      transpileBrowser::Transpile(&source_, is_linux_);
      transpileDialog::Transpile(&source_, is_linux_);
      transpileKeystrokes::Transpile(&source_, is_linux_);
      transpileTerminal::Transpile(&source_, is_linux_);

      contains_commands = SourceContainsCommands();

      ++runs;
    }
  } while (contains_commands && runs < 5);
}

bool S2sTranspiler::SourceContainsCommands() {
  std::regex exp("#[a-zA-Z]");

  return 0 < std::distance(  // Count the number of matches inside the iterator
      std::sregex_iterator(source_.begin(), source_.end(), exp),
      std::sregex_iterator());
}

bool S2sTranspiler::ParsePhp() {
  if (!helper::String::Contains(source_, "<?php")) return false;

  std::string phtml = source_;
  helper::String::ReplaceAll(&phtml, "#<?php", "<?php");

  InitPathPhtml();

  if (!helper::File::WriteToNewFile(path_phtml_file_abs_, phtml)) return false;

  std::string command = "php " + path_phtml_file_abs_;

  source_ = helper::Cli::GetExecutionResponse(command.c_str());

  return helper::File::Remove(path_phtml_file_abs_.c_str());
}

// 1. Transpile given *.do.sh file to *.sh,
// 2. Create temporary dosh copy of *.sh w/ dosh macros replaced
// 3. Execute dosh copy
// 4. Delete dosh copy
bool S2sTranspiler::Execute() {
  if (!Compile()) return false;

  InitPathFileRuntime();

  transpilePlatform::Transpile(&source_, is_linux_);
  runtimeOption::ReplaceRunTimeMacros(&source_, is_linux_);
  ParsePhp();

  SaveSourceToRuntimeScript();
  MakeRuntimeScriptExecutable();

  std::cout
      << helper::Cli::GetExecutionResponse(path_runtime_file_abs_.c_str());

  RemoveTemporaryExecutionFile();

  return true;
}

void S2sTranspiler::InitPathPhtml() {
  path_phtml_file_abs_= path_compiled_file_abs_ += ".phtml";
}

void S2sTranspiler::SaveSourceToRuntimeScript() {
  helper::File::WriteToNewFile(path_runtime_file_abs_, source_);
}

void S2sTranspiler::MakeRuntimeScriptExecutable() const {
  std::string command = "chmod +x " + path_runtime_file_abs_;

  helper::Cli::Execute(command.c_str());
}

bool S2sTranspiler::RemoveTemporaryExecutionFile() {
  return helper::String::Contains(source_, "#!keep_runtime_file")
    ? false
    : helper::File::Remove(path_runtime_file_abs_.c_str());
}

void S2sTranspiler::InitPathSourceDirectory() {
  auto offset_last_slash =
      static_cast<uint32_t>(helper::String::FindLast(
          path_source_file_abs_,
          "/",
          0,
          path_source_file_abs_.length()));

  path_source_directory_abs_ =
      path_source_file_abs_.substr(0, offset_last_slash) + "/";
}

void S2sTranspiler::InitPathFileCompiled() {
  if (helper::String::EndsWith(path_source_file_abs_, ".do.sh")) {
    path_compiled_file_abs_ =
        path_source_file_abs_.substr(0, path_source_file_abs_.length() - 6);
  }

  path_compiled_file_abs_ += ".x.sh";
}

void S2sTranspiler::InitPathFileRuntime() {
  path_runtime_file_abs_ = path_compiled_file_abs_ += ".run.sh";
}

bool S2sTranspiler::ResolveImports() {
  int32_t offset_start;

  helper::String::ReplaceAll(&source_, "::FILE::", path_source_file_abs_);
  ReplaceLineNumberMacros(&source_);

  while ((offset_start = source_.find("#import ")) != std::string::npos) {
    auto offset_end = source_.find('\n', offset_start);

    if (offset_end == std::string::npos) offset_end = source_.length();

    std::string path_import_file = source_.substr(
        offset_start + 7,
        offset_end - (offset_start + 7));
    helper::String::Trim(&path_import_file);

    if (!helper::File::ResolvePath(path_source_directory_abs_,
                                   &path_import_file,
                                   true)) {
      return doShell::AppLog::NotifyError(
          "Imported from " + path_source_file_abs_);
    }

    std::string import_content;
    helper::File::GetFileContents(path_import_file, &import_content);
    import_content += "\n";

    helper::String::ReplaceAll(&import_content, "::FILE::", path_import_file);
    ReplaceLineNumberMacros(&import_content);

    RemoveSheBangLine(&import_content);

    auto separation = helper::String::Repeat(
        "-",
        static_cast<u_int16_t>(67 - path_import_file.length()));

    import_content =
        std::string("# ").append(separation)
            .append(" imported: ").append(path_import_file).append("\n")
            .append(import_content).append("\n")
            .append("# ").append(separation)
            .append(" import end. \n").append("\n");

    source_.replace(offset_start, offset_end - offset_start, import_content);
  }

  return true;
}

int S2sTranspiler::ReplaceLineNumberMacros(std::string *code) {
  if (!helper::String::Contains(*code, "::LINE::")) return 0;

  std::string out;

  auto lines = helper::String::Explode(*code, '\n');
  int line_number = 1;

  for (std::string& line : lines) {
    helper::String::ReplaceAll(&line, "::LINE::", std::to_string(line_number));

    out += line + '\n';

    ++line_number;
  }

  *code = out;

  return true;
}

bool S2sTranspiler::CompileAllInPath() {
  // TODO(kay): implement
  return true;
}

bool S2sTranspiler::LoadSource() {
  auto pwd = std::getenv("PWD");

  path_source_file_abs_ = argv_[2];

  return helper::File::ResolvePath(pwd, &path_source_file_abs_, true)
         ? helper::File::GetFileContents(path_source_file_abs_, &source_)
         : false;
}

bool S2sTranspiler::RemoveSheBangLine(std::string *code) {
  auto offset_first_newline = code->find('\n');

  if (offset_first_newline == std::string::npos) return false;

  std::string first_line = code->substr(0, offset_first_newline);

  if (!helper::String::StartsWith(first_line.c_str(), "#!")) return false;

  *code = code->substr(offset_first_newline);

  return true;
}

// Remove multiple successive newlines
void S2sTranspiler::CleanupSource() {
  auto lines = helper::String::Explode(source_, '\n');

  std::string clean;

  bool prev_line_was_empty = false;

  for (auto line : lines) {
    helper::String::Trim(&line);

    if (line.empty()) {
      if (!prev_line_was_empty) clean += line + "\n";
      prev_line_was_empty = true;
    } else {
      clean += line + "\n";
      prev_line_was_empty = false;
    }
  }

  source_ = clean;
}

S2sTranspiler::~S2sTranspiler() {
}

}  // namespace doShell