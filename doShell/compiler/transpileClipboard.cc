// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#include <doShell/compiler/transpileClipboard.h>

namespace doShell {

void transpileClipboard::Transpile(std::string *code, bool is_linux) {
  TranspileSetClipboard(code, is_linux);
  TranspileCopyPaste(code, is_linux);
}

bool transpileClipboard::TranspileSetClipboard(std::string *code,
                                               bool is_linux) {
  std::string replacement =
      is_linux
      // TODO(kay): instead of commenting-out maintain text to be copied
      ? "echo 'https://www.github.com/' | xclip -sel clip #"
      : "osascript -e 'set the clipboard to \"https://www.github.com/\"'";

  return helper::String::ReplaceAll(
      code, "#setClipboard", replacement) > 0;
}

bool transpileClipboard::TranspileCopyPaste(std::string *code,
                                            bool is_linux) {
  std::string replacement =
      is_linux
      // TODO(kay): instead of commenting-out maintain text to be copied
      ? "echo 'https://www.github.com/' | xclip -sel clip #\n"
        "xdotool key ctrl+v"
      : "osascript -e 'set the clipboard to \"https://www.github.com/\"'\n"
        "osascript -e 'tell app \"System Events\" "
          "to keystroke \"v\" using command down'";

  return helper::String::ReplaceAll(
      code, "#copyPaste", replacement) > 0;
}
}  // namespace doShell
