// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#include <doShell/dosh/transpile/transpile_terminal.h>

namespace doShell {

transpileTerminal::transpileTerminal(std::string *code) {
  code_ = code;

  char *terminal = getenv("DOSH_TERMINAL");

  *terminal_ = nullptr == terminal || strlen(terminal) == 0
    ? "gnome-terminal"
    : terminal;
}

void transpileTerminal::Transpile(std::string *code) {
  if (!helper::String::Contains(*code, "Terminal")) return;

  auto *instance = new transpileTerminal(code);

#if __linux__
  // linux only: remember from which terminal doShell was invoked initially
  // for #activateTerminal to know which terminal instance to re-focus
  // via:  xdotool windowactivate $DOSH_TERMINAL
  // (mac os does that by itself)
  instance->has_terminal_window_id = true;

  std::string remember_terminal =
      "DOSH_TERMINAL=$(xdotool getactivewindow)\n";

  auto offset_insert = instance->code_->find("#!/usr/bin/env");

  if (offset_insert == std::string::npos) {
    *(instance->code_) = remember_terminal + *(instance->code_);
  } else {
    offset_insert = instance->code_->find("\n");

    *(instance->code_) =
        instance->code_->substr(0, offset_insert)
        + "\n\n" + remember_terminal
        + instance->code_->substr(offset_insert + 1);
  }
#endif

  instance
      ->TranspileActivate()
      ->TranspileCopyPasteInTerminal()
      ->TranspileHitCopyInTerminal()
      ->TranspileHitFindInTerminal()
      ->TranspilePasteInTerminal();

  delete instance;
}

transpileTerminal* transpileTerminal::TranspileActivate() {
  if (std::string::npos == code_->find("#activateTerminal")) return this;

  std::string replacement;

#if __linux__
  if (has_terminal_window_id) {
    // doShell runs initially from within a terminal window to return to
    replacement = "xdotool windowactivate \"$DOSH_TERMINAL\"\n";
  } else {
    // fallback: find/activate terminal window
    replacement =
        "if pidof -s " + *terminal_ + " > /dev/null; then\n"
          "    wmctrl -a " + *terminal_ + "\n"
        "else\n"
//          "    me=$SUDO_USER\n"
//          "    sudo -u $me nohup terminal > /dev/null &\n"
          "    nohup " + *terminal_ + " > /dev/null &\n"
        "fi";
  }
#else
  replacement = "osascript -e 'tell application \"Terminal\" to activate'";
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
    helper::String::ReplaceAll(
        code_,
        "#hitFindInTerminal",
        "xdotool key ctrl+shift+f");
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
    helper::String::ReplaceAll(
        code_,
        "#copyInTerminal",
        "xdotool key ctrl+shift+c");
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
    helper::String::ReplaceAll(
        code_,
        "#hitPasteInTerminal",
        "xdotool key ctrl+shift+v");
  #else
    helper::String::ReplaceAll(
      code_,
      "#hitPasteInTerminal",
      "osascript -e 'tell application \"System Events\" to keystroke \"v\" "
      "using {command down, option down}'");
  #endif

  return this;
}

void transpileTerminal::TranspileMute(std::string *code) {
  helper::String::ReplaceAll(code, "::MUTE::", "&>/dev/null");
  helper::String::ReplaceAll(code, "::MUTE_2::", "2>/dev/null");
}

}  // namespace doShell
