// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#include <doShell/compiler/compiler.h>

namespace doShell {

// Constructor: init (resolve) command and arguments
Compiler::Compiler(int argc, const std::vector<std::string> &argv) {
  argc_ = argc;
  argv_ = argv;

  // ...
}

bool Compiler::Compile() {
  if (argc_ <= 1) return CompileAllInPath();

  auto source = LoadSource();

  return true;
}

bool Compiler::CompileAllInPath() {
  // TODO(kay): implement
  return true;
}

std::string Compiler::LoadSource() {
  auto pwd = std::getenv("PWD");

  path_source_abs_ = argv_[2];

  if (!helper::File::ResolvePath(pwd, &path_source_abs_, true)) return "";

  std::string code;
  helper::File::GetFileContents(path_source_abs_, &code);

  return code;
}

Compiler::~Compiler() {

}

}  // namespace doShell
