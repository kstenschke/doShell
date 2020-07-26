// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#include <doShell/compiler/compiler.h>
#include <doShell/helper/helper_cli.h>

namespace doShell {

// Constructor: init (resolve) command and arguments
Compiler::Compiler(int argc, const std::vector<std::string> &argv) {
  argc_ = argc;
  argv_ = argv;

  // ...
}

// Transpile given *.do.sh file to *.sh
bool Compiler::Compile() {
  if (argc_ <= 1) return CompileAllInPath();

  if (!LoadSource()) return false;

  InitPathSourceDirectory();

  ResolveImports();

  // replace all runtime macros by generic values

  // detect OS
  // replace wait commands
  // replace keyboard commands
  //

  InitPathFileCompiled();

  helper::File::WriteToNewFile(path_compiled_file_abs_, source_);

  return true;
}

// 1. Transpile given *.do.sh file to *.sh,
// 2. Create temporary runtime copy of *.sh w/ runtime macros replaced
// 3. Execute runtime copy
// 4. Delete runtime copy
bool Compiler::Execute() {
  if (!Compile()) return false;

  InitPathFileRuntime();
  ReplaceRunTimeMacros();

  helper::Cli::GetExecutionResponse(path_runtime_file_abs_.c_str());

  return true;
}

bool Compiler::ReplaceRunTimeMacros() {
  if (helper::String::Contains(source_, "TIMESTAMP"))
    helper::String::ReplaceAll(&source_, "__TIMESTAMP__", helper::DateTime::GetTimestamp());

  return true;
}

void Compiler::InitPathSourceDirectory() {
  unsigned long offset_last_slash =
      static_cast<unsigned long>(helper::String::FindLast(
          path_source_file_abs_,
          "/",
          0,
          path_source_file_abs_.length()));

  path_source_directory_abs_ =
      path_source_file_abs_.substr(0, offset_last_slash) + "/";
}

void Compiler::InitPathFileCompiled() {
  if (helper::String::EndsWith(path_source_file_abs_, ".do.sh")) {
    path_compiled_file_abs_ =
        path_source_file_abs_.substr(0, path_source_file_abs_.length() - 8);
  }

  path_compiled_file_abs_ += ".sh";
}

void Compiler::InitPathFileRuntime() {
  path_compiled_file_abs_ = path_compiled_file_abs_ += ".run.sh";
}

bool Compiler::ResolveImports() {
  unsigned long offset_start;

  while ((offset_start = source_.find("#import ")) != std::string::npos) {
    unsigned long offset_end = source_.find('\n', offset_start);

    if (offset_end == std::string::npos) offset_end = source_.length();

    std::string path_import_file = source_.substr(
        offset_start + 7,
        offset_end - (offset_start + 7));
    helper::String::Trim(&path_import_file);

    if (!helper::File::ResolvePath(path_source_directory_abs_, &path_import_file, true)) {
      return doShell::AppLog::NotifyError("Imported from " + path_source_file_abs_);
    }

    std::string import_content;
    helper::File::GetFileContents(path_import_file, &import_content);
    import_content += "\n";

    source_.replace(offset_start, offset_end - offset_start, import_content);
  }

  return true;
}

bool Compiler::CompileAllInPath() {
  // TODO(kay): implement
  return true;
}

bool Compiler::LoadSource() {
  auto pwd = std::getenv("PWD");

  path_source_file_abs_ = argv_[2];

  return helper::File::ResolvePath(pwd, &path_source_file_abs_, true)
      ? helper::File::GetFileContents(path_source_file_abs_, &source_)
      : false;
}

Compiler::~Compiler() {

}

}  // namespace doShell
