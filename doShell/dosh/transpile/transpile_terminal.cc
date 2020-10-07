// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#include <doShell/dosh/transpile/transpile_terminal.h>

namespace doShell {

transpileTerminal::transpileTerminal(std::string *code) {
  code_ = code;
}

void transpileTerminal::Transpile(std::string *code) {
  if (!helper::String::Contains(*code, "Terminal")) return;

  auto *instance = new transpileTerminal(code);

  instance
    ->TranspileHitCopyInTerminal()
    ->TranspileHitFindInTerminal()
    ->TranspilePasteInTerminal();

  delete instance;
}

transpileTerminal* transpileTerminal::TranspileCopyPasteInTerminal() {
  if (std::string::npos == code_->find("#copyPaste ")) return this;

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

  *code_ = std::regex_replace(*code_, exp, replacement);

  return this;
}

transpileTerminal* transpileTerminal::TranspileHitFindInTerminal() {
  if (std::string::npos == code_->find("#hitFindInTerminal")) return this;

  #if __linux__
    helper::String::ReplaceAll(code, "#hitFindInTerminal", "xdotool key ctrl+shift+f");
  #else
    helper::String::ReplaceAll(
      code_,
      "#hitFindInTerminal",
      "osascript -e 'tell application \"System Events\" to keystroke \"f\" "
      "using {command down, option down}'");
  #endif

  return this;
}

transpileTerminal* transpileTerminal::TranspileHitCopyInTerminal() {
  if (std::string::npos == code_->find("#copyInTerminal ")) return this;

  #if __linux__
    helper::String::ReplaceAll(code, "#copyInTerminal", "xdotool key ctrl+shift+c");
  #else
    helper::String::ReplaceAll(
      code_,
      "#copyInTerminal",
      "osascript -e 'tell application \"System Events\" to keystroke \"c\" "
      "using {command down, option down}'");
  #endif

  return this;
}

transpileTerminal* transpileTerminal::TranspilePasteInTerminal() {
  if (std::string::npos == code_->find("#pasteInTerminal ")) return this;

  #if __linux__
    helper::String::ReplaceAll(code, "#pasteInTerminal", "xdotool key ctrl+shift+v");
  #else
    helper::String::ReplaceAll(
      code_,
      "#pasteInTerminal",
      "osascript -e 'tell application \"System Events\" to keystroke \"v\" "
      "using {command down, option down}'");
  #endif

  return this;
}

}  // namespace doShell
