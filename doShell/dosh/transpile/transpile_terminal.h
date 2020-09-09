// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#ifndef DOSHELL_DOSH_TRANSPILE_TRANSPILE_TERMINAL_H_
#define DOSHELL_DOSH_TRANSPILE_TRANSPILE_TERMINAL_H_

#include <doShell/helper/helper_string.h>
#include <string>

namespace doShell {
class transpileTerminal {
 public:
  static void Transpile(std::string *code, bool is_linux);

 private:
  static bool TranspileCopyPasteInTerminal(std::string *code, bool is_linux);
  static bool TranspileHitCopyInTerminal(std::string *code, bool is_linux);
  static bool TranspileHitFindInTerminal(std::string *code, bool is_linux);
  static bool TranspilePasteInTerminal(std::string *code, bool is_linux);
};
}  // namespace doShell

#endif  // DOSHELL_DOSH_TRANSPILE_TRANSPILE_TERMINAL_H_
