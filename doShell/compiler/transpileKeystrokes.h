// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#ifndef DOSHELL_COMPILER_TRANSPILEKEYSTROKES_H_
#define DOSHELL_COMPILER_TRANSPILEKEYSTROKES_H_

#include <doShell/helper/helper_string.h>

#include <string>

namespace doShell {
class transpileKeystrokes {
 public:
  static void Transpile(std::string *code, bool is_linux);

 private:
  static bool TranspileCopy(std::string *code, bool is_linux);
  static bool TranspileCut(std::string *code, bool is_linux);
  static bool TranspilePaste(std::string *code, bool is_linux);
  static bool TranspileSelectAll(std::string *code, bool is_linux);
  static bool TranspileHitKey(std::string *code, bool is_linux);
  static bool TranspileType(std::string *code, bool is_linux);
};
}  // namespace doShell

#endif  // DOSHELL_COMPILER_TRANSPILEKEYSTROKES_H_
