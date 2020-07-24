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
  return true;
}

Compiler::~Compiler() {
//  delete command_;
}

}  // namespace doShell
