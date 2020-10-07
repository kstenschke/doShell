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

void transpileTerminal::TranspileCopyPasteInTerminal(std::string *code) {
  if (std::string::npos == code->find("#copyPaste ")) return;

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
}

void transpileTerminal::TranspileHitFindInTerminal(std::string *code) {
  if (std::string::npos == code->find("#hitFindInTerminal")) return;

  #if __linux__
    helper::String::ReplaceAll(code, "#hitFindInTerminal", "xdotool key ctrl+shift+f");
  #else
    helper::String::ReplaceAll(
      code,
      "#hitFindInTerminal",
      "osascript -e 'tell application \"System Events\" to keystroke \"f\" "
      "using {command down, option down}'");
  #endif
}

void transpileTerminal::TranspileHitCopyInTerminal(std::string *code) {
  if (std::string::npos == code->find("#copyInTerminal ")) return;

  #if __linux__
    helper::String::ReplaceAll(code, "#copyInTerminal", "xdotool key ctrl+shift+c");
  #else
    helper::String::ReplaceAll(
      code,
      "#copyInTerminal",
      "osascript -e 'tell application \"System Events\" to keystroke \"c\" "
      "using {command down, option down}'");
  #endif
}

void transpileTerminal::TranspilePasteInTerminal(std::string *code) {
  if (std::string::npos == code->find("#pasteInTerminal ")) return;

  #if __linux__
    helper::String::ReplaceAll(code, "#pasteInTerminal", "xdotool key ctrl+shift+v");
  #else
    helper::String::ReplaceAll(
      code,
      "#pasteInTerminal",
      "osascript -e 'tell application \"System Events\" to keystroke \"v\" "
      "using {command down, option down}'");
  #endif
}

}  // namespace doShell
