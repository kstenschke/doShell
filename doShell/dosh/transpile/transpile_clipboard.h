// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#ifndef DOSHELL_DOSH_TRANSPILE_TRANSPILE_CLIPBOARD_H_
#define DOSHELL_DOSH_TRANSPILE_TRANSPILE_CLIPBOARD_H_

#include <doShell/helper/helper_string.h>
#include <string>

namespace doShell {
class transpileClipboard {
 public:
  static void Transpile(std::string *code);

 private:
  static void TranspileSetClipboard(std::string *code);

  static void TranspileCopyPaste(std::string *code);
  static void TranspileCopyAll(std::string *code);
  static void TranspileCutAll(std::string *code);

  static void TranspileAppendClipboardToFile(std::string *code);
  static void TranspileSaveClipboardToFile(std::string *code);
};
}  // namespace doShell

#endif  // DOSHELL_DOSH_TRANSPILE_TRANSPILE_CLIPBOARD_H_
