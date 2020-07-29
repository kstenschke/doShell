// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#include <doShell/compiler/transpileBrowser.h>

namespace doShell {
  bool transpileBrowser::TranspileActivate(std::string *code, bool is_linux) {
    return helper::String::ReplaceAll(
        code,
        "#activate browser",
        is_linux
        ? "if pidof -s firefox > /dev/null; then\n"
          "    wmctrl -a Firefox\n"
          "else\n"
//          "    me=$SUDO_USER\n"
//          "    sudo -u $me nohup firefox > /dev/null &\n"
          "    nohup firefox > /dev/null &\n"
          "fi"
        : "tell application \"Firefox\" to activate") > 0;
  }


  bool transpileBrowser::TranspileOpenUrlInNewBrowserTab(std::string *code,
                                                         bool is_linux) {
    return helper::String::ReplaceAll(
        code,
        "#open url in new browserTab:",
        is_linux
        ? "#open new browserTab\n"
          "sleep 0.3\n"
          "#focus browserURL\n"
          "sleep 0.3\n"
          "#type \"https://duckduckgo.com/\"\n"  // TODO(kay) make url dynamic
          "sleep 0.5\n"
          "#hit enter"
          "\n#"  // TODO(kay) remove comment-out url when replaced dynamically

        : "osascript -e 'tell application \"System Events\" "
          "to keystroke \"t\" using command down'") > 0;
  }

  bool transpileBrowser::TranspileOpenNewTab(std::string *code, bool is_linux) {
    return helper::String::ReplaceAll(
        code,
        "#open new browserTab",
        is_linux
          ? "xdotool key ctrl+t"
          : "osascript -e 'tell application \"System Events\" "
            "to keystroke \"t\" using command down'") > 0;
  }

  bool transpileBrowser::TranspileFocusUrl(std::string *code, bool is_linux) {
    return helper::String::ReplaceAll(
        code,
        "#focus browserURL",
        is_linux
          ? "xdotool key ctrl+l"
          : "osascript -e 'tell application \"System Events\" "
            "to keystroke \"l\" using command down'") > 0;
  }
}  // namespace doShell
