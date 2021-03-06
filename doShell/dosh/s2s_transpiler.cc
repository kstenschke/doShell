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
bool S2sTranspiler::Compile(bool overwrite_intermediary_file) {
  if (argc_ <= 1) return CompileAllInPath();

  if (!LoadSource()) return false;

  InitPathSourceDirectory();
  InitPathFileCompiled();

  if (!overwrite_intermediary_file
      && helper::File::FileExists(path_compiled_file_abs_))
    return helper::File::GetFileContents(path_compiled_file_abs_, &source_);

  ResolveImports();
  TranspileCommands();

  CleanupSource();
  TranspileSlowMotion();
  helper::File::WriteToNewFile(path_compiled_file_abs_, source_);

  return true;
}

void S2sTranspiler::TranspileCommands() {
  bool contains_commands;

  int runs = 0;

  do {
    if ((contains_commands = SourceContainsCommands())) {
      const char *path_binary_relative = argv_[0].c_str();
      auto path_binary = helper::File::GetAbsoluteFromRelativePath(
          path_binary_relative);

      transpileString::Transpile(&source_, path_binary, "");
      transpileString::Transpile(&source_, path_binary, "FromFile");

      transpileUrl::Transpile(&source_, path_binary);

      transpileRandom::Transpile(&source_);
      transpileClipboard::Transpile(&source_, &path_binary);
      transpileBrowser::Transpile(&source_);
      transpileDialog::Transpile(&source_);
      transpileKeystrokes::Transpile(&source_);
      transpileTerminal::Transpile(&source_);

      contains_commands = SourceContainsCommands();

      ++runs;
    }
  } while (contains_commands && runs < 5);

  transpileTerminal::TranspileMute(&source_);
}

bool S2sTranspiler::SourceContainsCommands() {
  std::regex exp("_[a-zA-Z]");

  return 0 < std::distance(  // Count the number of matches inside the iterator
      std::sregex_iterator(source_.begin(), source_.end(), exp),
      std::sregex_iterator());
}

void S2sTranspiler::TranspileRuntimeVariables() {
  if (argc_ < 4 || !helper::Json::IsJson(argv_[3])) return;

  helper::Json::stringReplaceByJsonTuples(&source_, argv_[3]);
}

bool S2sTranspiler::ParsePhp() {
  if (!helper::String::Contains(source_, "_php")) return false;

  std::string phtml = source_;
  helper::String::ReplaceAll(&phtml, "_php", "<?php");
  helper::String::ReplaceAll(&phtml, "_/php", "?>");

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

  transpilePlatform::Transpile(&source_);
  transpileMacros::Transpile(&source_);

  TranspileRuntimeVariables();
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

bool S2sTranspiler::RemoveIntermediaryCode() {
  // TODO(kay): bugfix - ex 10 does NOT remove correctly
  return helper::String::Contains(source_, "#!remove_transpilation")
    ? helper::File::Remove(path_compiled_file_abs_.c_str())
    : false;
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
  helper::String::ReplaceAll(&source_, "::DIR::", GetBasePathBySourceFile());

  ReplaceLineNumberMacros(&source_);

  while ((offset_start = source_.find("_import ")) != std::string::npos) {
    auto offset_end = source_.find('\n', offset_start);

    if (offset_end == std::string::npos) offset_end = source_.length();

    std::string path_import_file = source_.substr(
        offset_start + 7,
        offset_end - (offset_start + 7));
    helper::String::Trim(&path_import_file);

    if (!helper::File::ResolvePath(path_source_directory_abs_,
                                   &path_import_file,
                                   true)) {
      std::cerr << "Failed importing from " + path_source_file_abs_;

      return false;
    }

    std::string import_content;
    helper::File::GetFileContents(path_import_file, &import_content);
    import_content += "\n";

    helper::String::ReplaceAll(&import_content, "::FILE::", path_import_file);

    auto offset_end_path_dir = path_import_file.find_last_of('/');

    std::string path_import_dir =
        path_import_file.substr(0, offset_end_path_dir - 1);

    helper::String::ReplaceAll(&import_content, "::DIR::", path_import_dir);

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

std::string S2sTranspiler::GetBasePathBySourceFile() const {
  std::vector<std::string> parts =
      helper::String::Explode(path_source_file_abs_, '/');

  int index = 0;
  uint64_t amount_parts = parts.size();

  std::string path_file;

  for (auto &part : parts) {
    if (index == amount_parts - 1) break;

    path_file += part + "/";

    ++index;
  }

  return path_file;
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

  for (auto &line : lines) {
    if (helper::String::IsWhiteSpaceOrEmpty(line)) {
      if (!prev_line_was_empty) clean += line + "\n";
      prev_line_was_empty = true;
    } else {
      clean += line + "\n";
      prev_line_was_empty = false;
    }
  }

  source_ = clean;
}

void S2sTranspiler::TranspileSlowMotion() {
  if (std::string::npos == (&source_)->find("#!slow_motion")) return;

  auto lines = helper::String::Explode(source_, '\n');
  std::string slow_source;

  for (auto &line : lines) {
    slow_source += line + "\n";

    if (helper::String::IsExecutableBashLine(line))
      slow_source += "sleep 0.5\n";
  }

  source_ = slow_source;
}

S2sTranspiler::~S2sTranspiler() {
}

}  // namespace doShell
