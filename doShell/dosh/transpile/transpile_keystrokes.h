// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#ifndef DOSHELL_DOSH_TRANSPILE_TRANSPILE_KEYSTROKES_H_
#define DOSHELL_DOSH_TRANSPILE_TRANSPILE_KEYSTROKES_H_

#include <doShell/helper/helper_string.h>

#include <string>

namespace doShell {
class transpileKeystrokes {
 public:
  explicit transpileKeystrokes(std::string *code);
  static void Transpile(std::string *code);

 private:
  std::string *code_;

  transpileKeystrokes* TranspileHitCopy();
  transpileKeystrokes* TranspileHitFind();
  transpileKeystrokes* TranspileCut();
  transpileKeystrokes* TranspilePaste();
  transpileKeystrokes* TranspileSelectAll();

  transpileKeystrokes* TranspileHitBackspace();
  transpileKeystrokes* TranspileHitDelete();
  transpileKeystrokes* TranspileHitEnter();
  transpileKeystrokes* TranspileHitEsc();
  transpileKeystrokes* TranspileHitFunctionKeys();
  transpileKeystrokes* TranspileHitTab();

  transpileKeystrokes* TranspileType();
};
}  // namespace doShell

#endif  // DOSHELL_DOSH_TRANSPILE_TRANSPILE_KEYSTROKES_H_
