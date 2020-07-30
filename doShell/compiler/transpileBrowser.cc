// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#include <doShell/compiler/transpileBrowser.h>

namespace doShell {
  void transpileBrowser::Transpile(std::string *code, bool is_linux) {
    TranspileActivate(code, is_linux);
    TranspileOpenUrlInNewBrowserTab(code, is_linux);
    TranspileOpenNewTab(code, is_linux);
    TranspileFocusUrl(code, is_linux);
  }

  bool transpileBrowser::TranspileActivate(std::string *code, bool is_linux) {
    std::string replacement =
        is_linux
        ? "if pidof -s firefox > /dev/null; then\n"
          "    wmctrl -a Firefox\n"
          "else\n"
//          "    me=$SUDO_USER\n"
//          "    sudo -u $me nohup firefox > /dev/null &\n"
          "    nohup firefox > /dev/null &\n"
          "fi"
        : "osascript -e 'tell application \"Firefox\" to activate'";

    replacement += "\nsleep 0.3";

    return helper::String::ReplaceAll(
        code, "#activate browser", replacement) > 0;
  }


  bool transpileBrowser::TranspileOpenUrlInNewBrowserTab(std::string *code,
                                                         bool is_linux) {
    std::string replacement =
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
          "to keystroke \"t\" using command down'";

    return helper::String::ReplaceAll(
        code, "#open url in new browserTab:", replacement) > 0;
  }

  bool transpileBrowser::TranspileOpenNewTab(std::string *code, bool is_linux) {
    std::string replacement =
        is_linux
        ? "xdotool key ctrl+t"
        : "osascript -e 'tell application \"System Events\" "
          "to keystroke \"t\" using command down'";

    replacement += "\nsleep 0.1";

    return helper::String::ReplaceAll(
        code, "#open new browserTab", replacement) > 0;
  }

  bool transpileBrowser::TranspileFocusUrl(std::string *code, bool is_linux) {
    std::string replacement =
        is_linux
        ? "xdotool key ctrl+l"
        : "osascript -e 'tell application \"System Events\" "
          "to keystroke \"l\" using command down'";

    replacement += "\nsleep 0.1";

    return helper::String::ReplaceAll(
        code, "#focus browserURL", replacement) > 0;
  }
}  // namespace doShell
