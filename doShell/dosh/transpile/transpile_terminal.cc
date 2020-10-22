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
      ->TranspileActivate()
      ->TranspileActivate()
      ->TranspileActivate()
      ->TranspileActivate();

  delete instance;
}

transpileTerminal* transpileTerminal::TranspileActivate() {
  if (std::string::npos == code_->find("#activateTerminal")) return this;

#if __linux__
  std::string replacement =
        "if pidof -s terminal > /dev/null; then\n"
        "    wmctrl -a terminal\n"
        "else\n"
//          "    me=$SUDO_USER\n"
//          "    sudo -u $me nohup terminal > /dev/null &\n"
        "    nohup terminal > /dev/null &\n"
        "fi"
#else
  std::string replacement =
      "osascript -e 'tell application \"Terminal\" to activate'";
#endif

  replacement += "\nsleep 0.2";

  helper::String::ReplaceAll(code_, "#activateTerminal", replacement);

  return this;
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
  if (std::string::npos == code_->find("#hitPasteInTerminal ")) return this;

  #if __linux__
    helper::String::ReplaceAll(code, "#hitPasteInTerminal", "xdotool key ctrl+shift+v");
  #else
    helper::String::ReplaceAll(
      code_,
      "#hitPasteInTerminal",
      "osascript -e 'tell application \"System Events\" to keystroke \"v\" "
      "using {command down, option down}'");
  #endif

  return this;
}

}  // namespace doShell
