// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#include <doShell/dosh/transpile/transpileTerminal.h>

namespace doShell {

void transpileTerminal::Transpile(std::string *code, bool is_linux) {
  if (!helper::String::Contains(*code, "Terminal")) return;

  TranspileHitCopyInTerminal(code, is_linux);
  TranspileHitFindInTerminal(code, is_linux);
  TranspilePasteInTerminal(code, is_linux);
}

bool transpileTerminal::TranspileCopyPasteInTerminal(std::string *code,
                                                     bool is_linux) {
  if (std::string::npos == code->find("#copyPaste ")) return false;

  std::string replacement =
      is_linux
      ? "echo '$1' | xclip -sel clip #\n"
        "xdotool key ctrl+shift+v"
      : "osascript -e 'set the clipboard to \"$1\"'\n"
        "osascript -e 'tell app \"System Events\" "
        "to keystroke \"v\" using {command down, option down}'";

  std::regex exp(R"(#copyPaste \"(.*)\")");

  *code = std::regex_replace(*code, exp, replacement);

  return true;
}

bool transpileTerminal::TranspileHitFindInTerminal(std::string *code,
                                                     bool is_linux) {
  if (std::string::npos == code->find("#hitFindInTerminal")) return false;

  return helper::String::ReplaceAll(
      code,
      "#hitFindInTerminal",
      is_linux
      ? "xdotool key ctrl+shift+f"
      : "osascript -e 'tell application \"System Events\" to keystroke \"f\" "
        "using {command down, option down}'") > 0;
}

bool transpileTerminal::TranspileHitCopyInTerminal(std::string *code,
                                                     bool is_linux) {
  if (std::string::npos == code->find("#copyInTerminal ")) return false;

  return helper::String::ReplaceAll(
      code,
      "#copyInTerminal",
      is_linux
      ? "xdotool key ctrl+shift+c"
      : "osascript -e 'tell application \"System Events\" to keystroke \"c\" "
        "using {command down, option down}'") > 0;
}

bool transpileTerminal::TranspilePasteInTerminal(std::string *code,
                                                   bool is_linux) {
  if (std::string::npos == code->find("#pasteInTerminal ")) return false;

  return helper::String::ReplaceAll(
      code,
      "#pasteInTerminal",
      is_linux
      ? "xdotool key ctrl+shift+v"
      : "osascript -e 'tell application \"System Events\" to keystroke \"v\" "
        "using {command down, option down}'") > 0;
}

}  // namespace doShell
