// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#ifndef DOSHELL_DOSH_TRANSPILE_TRANSPILE_TERMINAL_H_
#define DOSHELL_DOSH_TRANSPILE_TRANSPILE_TERMINAL_H_

#include <doShell/helper/helper_string.h>
#include <string>

namespace doShell {
class transpileTerminal {
 public:
  static void Transpile(std::string *code);

 private:
  static void TranspileCopyPasteInTerminal(std::string *code);
  static void TranspileHitCopyInTerminal(std::string *code);
  static void TranspileHitFindInTerminal(std::string *code);
  static void TranspilePasteInTerminal(std::string *code);
};
}  // namespace doShell

#endif  // DOSHELL_DOSH_TRANSPILE_TRANSPILE_TERMINAL_H_
