// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#ifndef DOSHELL_DOSH_TRANSPILE_TRANSPILE_CLIPBOARD_H_
#define DOSHELL_DOSH_TRANSPILE_TRANSPILE_CLIPBOARD_H_

#include <doShell/helper/helper_string.h>
#include <string>

namespace doShell {
class transpileClipboard {
 public:
  explicit transpileClipboard(std::string *code, std::string *path_binary);
  static void Transpile(std::string *code, std::string *path_binary);

 private:
  std::string *code_;
  std::string *path_binary_;

  transpileClipboard* TranspileGetClipboard();
  transpileClipboard* TranspileSetClipboard();

  transpileClipboard* TranspileCopyPaste();
  transpileClipboard* TranspileCopyAll();
  transpileClipboard* TranspileCutAll();

  transpileClipboard* TranspileAppendClipboardToFile();
  transpileClipboard* TranspileLoadIntoClipboard();
  transpileClipboard* TranspileSaveClipboard();

  transpileClipboard* TranspilePasteRenderedFromFile();

  transpileClipboard* TranspilePregMatchAllInClipboard();

  transpileClipboard* TranspileCommand(const std::string &command,
                                       int amount_args = 2);
};
}  // namespace doShell

#endif  // DOSHELL_DOSH_TRANSPILE_TRANSPILE_CLIPBOARD_H_
