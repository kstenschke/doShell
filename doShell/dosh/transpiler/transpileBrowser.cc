// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#include <doShell/dosh/transpiler/transpileBrowser.h>

namespace doShell {
  void transpileBrowser::Transpile(std::string *code, bool is_linux) {
    TranspileActivate(code, is_linux);
    TranspileOpenUrlInNewBrowserTab(code, is_linux);
    TranspileOpenNewTab(code, is_linux);
    TranspileFocusUrl(code, is_linux);
    TranspileOpenBrowserDevTools(code, is_linux);
    TranspileOpenBrowserDevConsole(code, is_linux);
  }

  bool transpileBrowser::TranspileActivate(std::string *code, bool is_linux) {
    if (std::string::npos == code->find("#activateBrowser")) return false;

    std::string replacement =
        is_linux
        ? "if pidof -s firefox > /dev/null; then\n"
          "    wmctrl -a Firefox\n"
          "else\n"
//          "    me=$SUDO_USER\n"
//          "    sudo -u $me nohup firefox > /dev/null &\n"
          "    nohup firefox > /dev/null &\n"
          "fi"
//        : "osascript -e 'tell application \"Firefox\" to activate'";
        : "osascript -e 'tell application \"Chromium\" to activate'";

    replacement += "\nsleep 0.3";

    return helper::String::ReplaceAll(
        code, "#activateBrowser", replacement) > 0;
  }


  bool transpileBrowser::TranspileOpenUrlInNewBrowserTab(std::string *code,
                                                         bool is_linux) {
    if (std::string::npos == code->find("#openUrlInNewBrowserTab")) return false;

    std::string replacement =
        "#openNewBrowserTab\n"
        "#focusBrowserURL\n"
        "#copyPaste: '$1/'\n"
        "#hit enter";

    std::regex exp(R"(#openUrlInNewBrowserTab \"(.*)\")");
    *code = std::regex_replace(*code, exp, replacement);

    return true;
  }

  bool transpileBrowser::TranspileOpenNewTab(std::string *code, bool is_linux) {
    if (std::string::npos == code->find("#openNewBrowserTab")) return false;

    std::string replacement =
        is_linux
        ? "xdotool key ctrl+t"
        : "osascript -e 'tell application \"System Events\" "
          "to keystroke \"t\" using command down'";

    replacement += "\nsleep 0.1";

    return helper::String::ReplaceAll(
        code, "#openNewBrowserTab", replacement) > 0;
  }

  bool transpileBrowser::TranspileOpenBrowserDevTools(std::string *code, bool is_linux) {
    if (std::string::npos == code->find("#openBrowserDevTools")) return false;

    std::string replacement =
        is_linux
        ? "xdotool key f12"
        : "osascript -e 'tell application \"System Events\" "
          "to keystroke \"F12\"'";

    replacement += "\nsleep 0.1";

    return helper::String::ReplaceAll(
        code, "#openBrowserDevTools", replacement) > 0;
  }

  bool transpileBrowser::TranspileOpenBrowserDevConsole(std::string *code, bool is_linux) {
    if (std::string::npos == code->find("#openBrowserDevConsole")) return false;

    std::string replacement =
        is_linux
        ? "xdotool key f12"
        : "osascript -e 'tell application \"System Events\" "
          "to keystroke \"F12\"'"
          "osascript -e 'tell application \"System Events\" "
          "to keystroke \"p\" with {command down, shift down} '";  // chromium

    replacement += "\nsleep 0.1";

    return helper::String::ReplaceAll(
        code, "#openBrowserDevConsole", replacement) > 0;
  }

  bool transpileBrowser::TranspileFocusUrl(std::string *code, bool is_linux) {
    if (std::string::npos == code->find("#focusBrowserURL")) return false;

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
/*
(()=>{
data=new FormData();
data.set('html',document.documentElement.innerHTML);
req=new XMLHttpRequest();
req.open("POST", 'http://localhost:8765', true);
req.send(data);
})()
*/