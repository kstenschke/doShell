// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#ifndef DOSHELL_COMPILER_TRANSPILECONTROLFLOW_H_
#define DOSHELL_COMPILER_TRANSPILECONTROLFLOW_H_

#include <doShell/helper/helper_string.h>

#include <string>

namespace doShell {
class transpileControlFlow {
 public:
  static bool TranspileWait(std::string *code, bool is_linux);
};
}  // namespace doShell

#endif  // DOSHELL_COMPILER_TRANSPILECONTROLFLOW_H_
