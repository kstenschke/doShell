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
    if (std::string::npos == code->find("#activateBrowser ")) return false;

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
        code, "#activateBrowser", replacement) > 0;
  }


  bool transpileBrowser::TranspileOpenUrlInNewBrowserTab(std::string *code,
                                                         bool is_linux) {
    if (std::string::npos==code->find("#openUrlInNewBrowserTab ")) return false;

    std::string replacement =
        "#activate browser\n"
            "#open new browserTab\n"
            "#focus browserURL\n"
            "#copyPaste: '$1/'\n"
            "#hit enter";

    std::regex exp(R"(#openUrlInNewBrowserTab \"(.*)\")");
    *code = std::regex_replace(*code, exp, replacement);

    return true;
  }

  bool transpileBrowser::TranspileOpenNewTab(std::string *code, bool is_linux) {
    if (std::string::npos == code->find("#openNewBrowserTab ")) return false;

    std::string replacement =
        is_linux
        ? "xdotool key ctrl+t"
        : "osascript -e 'tell application \"System Events\" "
          "to keystroke \"t\" using command down'";

    replacement += "\nsleep 0.1";

    return helper::String::ReplaceAll(
        code, "#openNewBrowserTab", replacement) > 0;
  }

  bool transpileBrowser::TranspileFocusUrl(std::string *code, bool is_linux) {
    if (std::string::npos == code->find("#focusBrowserURL ")) return false;

    std::string replacement =
        is_linux
        ? "xdotool key ctrl+l"
        : "osascript -e 'tell application \"System Events\" "
          "to keystroke \"l\" using command down'";

    replacement += "\nsleep 0.1";

    return helper::String::ReplaceAll(
        code, "#focusBrowserURL", replacement) > 0;
  }

  bool transpileBrowser::TranspileSendJsResult(std::string *code, bool is_linux) {
    return helper::String::ReplaceAll(
        code,
        "#getBrowserHtml",
          "(()=>{\n"
            "data=new FormData();\n"
            "data.set('html',document.documentElement.innerHTML);\n"
            "req=new XMLHttpRequest();\n"
            "req.open(\"POST\", 'http://localhost:8765', true);\n"
            "req.send(data);\n"
            "})()"
    ) > 0;
  }
}  // namespace doShell
