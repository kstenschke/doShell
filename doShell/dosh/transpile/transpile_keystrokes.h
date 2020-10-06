// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#ifndef DOSHELL_DOSH_TRANSPILE_TRANSPILE_KEYSTROKES_H_
#define DOSHELL_DOSH_TRANSPILE_TRANSPILE_KEYSTROKES_H_

#include <doShell/helper/helper_string.h>

#include <string>

namespace doShell {
class transpileKeystrokes {
 public:
  static void Transpile(std::string *code);

 private:
  static bool TranspileHitCopy(std::string *code);
  static bool TranspileHitFind(std::string *code);
  static bool TranspileCut(std::string *code);
  static bool TranspilePaste(std::string *code);
  static bool TranspileSelectAll(std::string *code);

  static bool TranspileHitBackspace(std::string *code);
  static bool TranspileHitDelete(std::string *code);
  static bool TranspileHitEnter(std::string *code);
  static bool TranspileHitEsc(std::string *code);
  static bool TranspileHitFunctionKeys(std::string *code);
  static bool TranspileHitTab(std::string *code);

  static bool TranspileType(std::string *code);
};
}  // namespace doShell

#endif  // DOSHELL_DOSH_TRANSPILE_TRANSPILE_KEYSTROKES_H_
