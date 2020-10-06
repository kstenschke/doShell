// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#include <doShell/dosh/transpile/transpile_terminal.h>

namespace doShell {

void transpileTerminal::Transpile(std::string *code) {
  if (!helper::String::Contains(*code, "Terminal")) return;

  TranspileHitCopyInTerminal(code);
  TranspileHitFindInTerminal(code);
  TranspilePasteInTerminal(code);
}

bool transpileTerminal::TranspileCopyPasteInTerminal(std::string *code) {
  if (std::string::npos == code->find("#copyPaste ")) return false;

  #if __linux__
    std::string replacement =
      "echo '$1' | xclip -sel clip #\n"
      "xdotool key ctrl+shift+v";
  #else
    std::string replacement =
      "osascript -e 'set the clipboard to \"$1\"'\n"
      "osascript -e 'tell app \"System Events\" "
      "to keystroke \"v\" using {command down, option down}'";
  #endif

  std::regex exp(R"(#copyPaste \"(.*)\")");

  *code = std::regex_replace(*code, exp, replacement);

  return true;
}

bool transpileTerminal::TranspileHitFindInTerminal(std::string *code) {
  if (std::string::npos == code->find("#hitFindInTerminal")) return false;

  #if __linux__
    return helper::String::ReplaceAll(
      code, "#hitFindInTerminal", "xdotool key ctrl+shift+f") > 0;
  #else
    return helper::String::ReplaceAll(
      code,
      "#hitFindInTerminal",
      "osascript -e 'tell application \"System Events\" to keystroke \"f\" "
      "using {command down, option down}'") > 0;
  #endif
}

bool transpileTerminal::TranspileHitCopyInTerminal(std::string *code) {
  if (std::string::npos == code->find("#copyInTerminal ")) return false;

  #if __linux__
    return helper::String::ReplaceAll(
      code,
      "#copyInTerminal",
      "xdotool key ctrl+shift+c") > 0;
  #else
    return helper::String::ReplaceAll(
      code,
      "#copyInTerminal",
      "osascript -e 'tell application \"System Events\" to keystroke \"c\" "
      "using {command down, option down}'") > 0;
  #endif
}

bool transpileTerminal::TranspilePasteInTerminal(std::string *code) {
  if (std::string::npos == code->find("#pasteInTerminal ")) return false;

  #if __linux__
    return helper::String::ReplaceAll(
      code, "#pasteInTerminal", "xdotool key ctrl+shift+v") > 0;
  #else
    return helper::String::ReplaceAll(
      code,
      "#pasteInTerminal",
      "osascript -e 'tell application \"System Events\" to keystroke \"v\" "
      "using {command down, option down}'") > 0;
  #endif
}

}  // namespace doShell
