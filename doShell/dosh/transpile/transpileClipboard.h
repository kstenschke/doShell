// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#ifndef DOSHELL_DOSH_TRANSPILE_TRANSPILECLIPBOARD_H_
#define DOSHELL_DOSH_TRANSPILE_TRANSPILECLIPBOARD_H_

#include <doShell/helper/helper_string.h>
#include <string>

namespace doShell {
class transpileClipboard {
 public:
  static void Transpile(std::string *code, bool is_linux);

 private:
  static bool TranspileSetClipboard(std::string *code, bool is_linux);

  static bool TranspileCopyPaste(std::string *code, bool is_linux);
  static bool TranspileCopyAll(std::string *code, bool is_linux);
  static bool TranspileCutAll(std::string *code, bool is_linux);

  static bool TranspileAppendClipboardToFile(std::string *code, bool is_linux);
  static bool TranspileSaveClipboardToFile(std::string *code, bool is_linux);
};
}  // namespace doShell

#endif  // DOSHELL_DOSH_TRANSPILE_TRANSPILECLIPBOARD_H_