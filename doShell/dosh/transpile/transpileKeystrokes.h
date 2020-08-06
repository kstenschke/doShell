// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#ifndef DOSHELL_DOSH_TRANSPILE_TRANSPILEKEYSTROKES_H_
#define DOSHELL_DOSH_TRANSPILE_TRANSPILEKEYSTROKES_H_

#include <doShell/helper/helper_string.h>

#include <string>

namespace doShell {
class transpileKeystrokes {
 public:
  static void Transpile(std::string *code, bool is_linux);

 private:
  static bool TranspileHitCopy(std::string *code, bool is_linux);
  static bool TranspileHitFind(std::string *code, bool is_linux);
  static bool TranspileCut(std::string *code, bool is_linux);
  static bool TranspilePaste(std::string *code, bool is_linux);
  static bool TranspileSelectAll(std::string *code, bool is_linux);

  static bool TranspileHitCopyInTerminal(std::string *code, bool is_linux);
  static bool TranspileHitFindInTerminal(std::string *code, bool is_linux);
  static bool TranspilePasteInTerminal(std::string *code, bool is_linux);

  static bool TranspileHitBackspace(std::string *code, bool is_linux);
  static bool TranspileHitDelete(std::string *code, bool is_linux);
  static bool TranspileHitEnter(std::string *code, bool is_linux);
  static bool TranspileHitEsc(std::string *code, bool is_linux);
  static bool TranspileHitFunctionKeys(std::string *code, bool is_linux);
  static bool TranspileHitTab(std::string *code, bool is_linux);

  static bool TranspileType(std::string *code, bool is_linux);
};
}  // namespace doShell

#endif  // DOSHELL_DOSH_TRANSPILE_TRANSPILEKEYSTROKES_H_
