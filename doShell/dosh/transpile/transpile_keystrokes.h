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
  static void TranspileHitCopy(std::string *code);
  static void TranspileHitFind(std::string *code);
  static void TranspileCut(std::string *code);
  static void TranspilePaste(std::string *code);
  static void TranspileSelectAll(std::string *code);

  static void TranspileHitBackspace(std::string *code);
  static void TranspileHitDelete(std::string *code);
  static void TranspileHitEnter(std::string *code);
  static void TranspileHitEsc(std::string *code);
  static void TranspileHitFunctionKeys(std::string *code);
  static void TranspileHitTab(std::string *code);

  static void TranspileType(std::string *code);
};
}  // namespace doShell

#endif  // DOSHELL_DOSH_TRANSPILE_TRANSPILE_KEYSTROKES_H_
