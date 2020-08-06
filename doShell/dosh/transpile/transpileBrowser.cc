// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#include <doShell/dosh/transpile/transpileBrowser.h>

namespace doShell {
  void transpileBrowser::Transpile(std::string *code, bool is_linux) {
    TranspileActivate(code, is_linux);
    TranspileOpenUrlInNewBrowserTab(code, is_linux);
    TranspileOpenNewTab(code, is_linux);
    TranspileFocusUrl(code, is_linux);
    TranspileOpenBrowserDevTools(code, is_linux);
    TranspileActivateDevConsole(code, is_linux);
    TranspileRunJs(code, is_linux);
    TranspileExecDevConsole(code, is_linux);
    TranspileClearDevConsole(code, is_linux);
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
        : "osascript -e 'tell application \"Firefox\" to activate'";

    replacement += "\nsleep 0.3";

    return helper::String::ReplaceAll(
        code, "#activateBrowser", replacement) > 0;
  }


  bool transpileBrowser::TranspileOpenUrlInNewBrowserTab(std::string *code,
                                                         bool is_linux) {
    if (std::string::npos == code->find("#openUrlInNewBrowserTab "))
      return false;

    std::string replacement =
        "#openNewBrowserTab\n"
        "#focusBrowserURL\n"
        "#copyPaste \"$1/\"\n"
        "sleep 0.2\n"
        "#hitEnter";

    std::regex exp(R"(#openUrlInNewBrowserTab \"(.*)\")");
    *code = std::regex_replace(*code, exp, replacement);

//    transpileClipboard::Transpile(code, is_linux);

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

  bool transpileBrowser::TranspileOpenBrowserDevTools(
      std::string *code, bool is_linux) {
    if (std::string::npos == code->find("#openBrowserDevTools")) return false;

    std::string replacement =
        is_linux
        ? "xdotool key F12"
        : "osascript -e 'tell application \"System Events\" "
          "to keystroke \"F12\"'";

    replacement += "\nsleep 0.5";

    return helper::String::ReplaceAll(
        code, "#openBrowserDevTools", replacement) > 0;
  }

  bool transpileBrowser::TranspileActivateDevConsole(
      std::string *code, bool is_linux) {
    if (std::string::npos == code->find("#openBrowserDevConsole")) return false;

    std::string replacement =
        is_linux
        ? "xdotool key ctrl+shift+k"
        : "osascript -e 'tell application \"System Events\" "
          "to keystroke \"k\" using {command down, option down}'\n";

    replacement += "\nsleep 0.5";

    return helper::String::ReplaceAll(
        code, "#openBrowserDevConsole", replacement) > 0;
  }

  bool transpileBrowser::TranspileRunJs(std::string *code, bool is_linux) {
    if (std::string::npos == code->find("#runJs")) return false;

    std::string replacement =
        "#openBrowserDevConsole\n"
        "#copyPaste \"$1\"\n"
        "sleep 0.1\n"
        "#execDevConsole";

    std::regex exp(R"(#runJs \"(.*)\")");
    *code = std::regex_replace(*code, exp, replacement);

    return true;
  }

  bool transpileBrowser::TranspileExecDevConsole(
      std::string *code, bool is_linux) {
    if (std::string::npos == code->find("#execDevConsole")) return false;

    std::string replacement =
        is_linux
        ? "xdotool key ctrl+KP_Enter"
        : "osascript -e 'tell application \"System Events\" "
            "to key code 36 using command down'";

    return helper::String::ReplaceAll(
        code, "#execDevConsole", replacement) > 0;
  }

  bool transpileBrowser::TranspileClearDevConsole(
      std::string *code, bool is_linux) {
    if (std::string::npos == code->find("#clearDevConsole")) return false;

    std::string replacement =
        "#openBrowserDevConsole\n"
        "#selectAll\n"
        "#hitBackspace\n";

    return helper::String::ReplaceAll(
        code, "#clearDevConsole", replacement) > 0;
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

  bool transpileBrowser::TranspileSendJsResult(
      std::string *code, bool is_linux) {
    return helper::String::ReplaceAll(
        code,
        "#getBrowserHtml",
          "(()=>{\n"
            "data=new FormData();\n"
            "data.set('html',document.documentElement.innerHTML);\n"
            "req=new XMLHttpRequest();\n"
            "req.open(\"POST\", 'http://localhost:8765', true);\n"
            "req.send(data);\n"
            "})()") > 0;
  }
}  // namespace doShell

/*
(()=>{
data=new FormData();
data.set('html',document.documentElement.innerHTML);
req=new XMLHttpRequest();
req.open("POST", 'http://localhost:8765', true);
req.send(data);
})()*/
