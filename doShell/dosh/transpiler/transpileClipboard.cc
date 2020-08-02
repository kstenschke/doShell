// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#include <doShell/dosh/transpiler/transpileClipboard.h>

namespace doShell {

void transpileClipboard::Transpile(std::string *code, bool is_linux) {
  TranspileSetClipboard(code, is_linux);
  TranspileCopyPaste(code, is_linux);
  TranspileSaveClipboardToFile(code, is_linux);
}

bool transpileClipboard::TranspileSetClipboard(std::string *code,
                                               bool is_linux) {
  if (std::string::npos == code->find("#setClipboard ")) return false;

  std::string replacement =
      is_linux
      ? "echo '$1' | xclip -sel clip #"
      : "osascript -e 'set the clipboard to \"$1\"'";

  std::regex exp (R"(#setClipboard \"(.*)\")");
  *code = std::regex_replace(*code, exp, replacement);

  return true;
}

bool transpileClipboard::TranspileSaveClipboardToFile(std::string *code,
                                               bool is_linux) {
  if (std::string::npos == code->find("#saveClipboardToFile ")) return false;

  std::string replacement =
      "/Users/kay/CLionProjects/robo/bin/mac/dosh saveClipboardToFile $1";

  std::regex exp (R"(#saveClipboardToFile \"(.*)\")");
  *code = std::regex_replace(*code, exp, replacement);

  return true;
}

bool transpileClipboard::TranspileCopyPaste(std::string *code,
                                            bool is_linux) {
  if (std::string::npos == code->find("#copyPaste ")) return false;

  std::string replacement =
      is_linux
      ? "echo '$1' | xclip -sel clip #\n"
        "xdotool key ctrl+v"
      : "osascript -e 'set the clipboard to \"$1\"'\n"
        "osascript -e 'tell app \"System Events\" "
          "to keystroke \"v\" using command down'";

  std::regex exp (R"(#copyPaste \"(.*)\")");

  *code = std::regex_replace(*code, exp, replacement);

  return true;
}
}  // namespace doShell
