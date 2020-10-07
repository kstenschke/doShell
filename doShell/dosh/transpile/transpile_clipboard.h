// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#ifndef DOSHELL_DOSH_TRANSPILE_TRANSPILE_CLIPBOARD_H_
#define DOSHELL_DOSH_TRANSPILE_TRANSPILE_CLIPBOARD_H_

#include <doShell/helper/helper_string.h>
#include <string>

namespace doShell {
class transpileClipboard {
 public:
  explicit transpileClipboard(std::string *code);
  static void Transpile(std::string *code);

 private:
  std::string *code_;

  transpileClipboard* TranspileSetClipboard();

  transpileClipboard* TranspileCopyPaste();
  transpileClipboard* TranspileCopyAll();
  transpileClipboard* TranspileCutAll();

  transpileClipboard* TranspileAppendClipboardToFile();
  transpileClipboard* TranspileSaveClipboardToFile();
};
}  // namespace doShell

#endif  // DOSHELL_DOSH_TRANSPILE_TRANSPILE_CLIPBOARD_H_
