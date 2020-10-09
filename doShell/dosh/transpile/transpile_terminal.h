// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#ifndef DOSHELL_DOSH_TRANSPILE_TRANSPILE_TERMINAL_H_
#define DOSHELL_DOSH_TRANSPILE_TRANSPILE_TERMINAL_H_

#include <doShell/helper/helper_string.h>
#include <string>

namespace doShell {
class transpileTerminal {
 public:
  explicit transpileTerminal(std::string *code);
  static void Transpile(std::string *code);

 private:
  std::string *code_;

  transpileTerminal* TranspileActivate();
  transpileTerminal* TranspileCopyPasteInTerminal();
  transpileTerminal* TranspileHitCopyInTerminal();
  transpileTerminal* TranspileHitFindInTerminal();
  transpileTerminal* TranspilePasteInTerminal();
};
}  // namespace doShell

#endif  // DOSHELL_DOSH_TRANSPILE_TRANSPILE_TERMINAL_H_
