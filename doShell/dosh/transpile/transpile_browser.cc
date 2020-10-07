// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#include <doShell/dosh/transpile/transpile_browser.h>

namespace doShell {
  void transpileBrowser::Transpile(std::string *code) {
    TranspileActivate(code);
    TranspileOpenUrlInNewBrowserTab(code);
    TranspileOpenNewTab(code);
    TranspileFocusUrl(code);
    TranspileOpenBrowserDevTools(code);
    TranspileActivateDevConsole(code);
    TranspileRunJs(code);
    TranspileExecDevConsole(code);
    TranspileClearDevConsole(code);
  }

  void transpileBrowser::TranspileActivate(std::string *code) {
    if (std::string::npos == code->find("#activateBrowser")) return;

    #if __linux__
    std::string replacement =
          "if pidof -s firefox > /dev/null; then\n"
          "    wmctrl -a Firefox\n"
          "else\n"
//          "    me=$SUDO_USER\n"
//          "    sudo -u $me nohup firefox > /dev/null &\n"
          "    nohup firefox > /dev/null &\n"
          "fi"
    #else
      std::string replacement =
          "osascript -e 'tell application \"Firefox\" to activate'";
    #endif

    replacement += "\nsleep 0.3";

    helper::String::ReplaceAll(code, "#activateBrowser", replacement);
  }


  void transpileBrowser::TranspileOpenUrlInNewBrowserTab(std::string *code) {
    if (std::string::npos == code->find("#openUrlInNewBrowserTab ")) return;

    std::string replacement =
        "#openNewBrowserTab\n"
        "#focusBrowserURL\n"
        "#copyPaste \"$1/\"\n"
        "sleep 0.2\n"
        "#hitEnter";

    std::regex exp(R"(#openUrlInNewBrowserTab \"(.*)\")");
    *code = std::regex_replace(*code, exp, replacement);

//    transpileClipboard::Transpile(code, is_linux);
  }

  void transpileBrowser::TranspileOpenNewTab(std::string *code) {
    if (std::string::npos == code->find("#openNewBrowserTab")) return;

    #if __linux__
      std::string replacement = "xdotool key ctrl+t";
    #else
      std::string replacement =
          "osascript -e 'tell application \"System Events\" "
          "to keystroke \"t\" using command down'";
    #endif

    replacement += "\nsleep 0.1";

    helper::String::ReplaceAll(code, "#openNewBrowserTab", replacement);
  }

  void transpileBrowser::TranspileOpenBrowserDevTools(std::string *code) {
    if (std::string::npos == code->find("#openBrowserDevTools")) return;

    #if __linux__
      std::string replacement = "xdotool key F12";
    #else
    std::string replacement =
        "osascript -e 'tell application \"System Events\" "
        "to keystroke \"F12\"'";
    #endif

    replacement += "\nsleep 0.5";

    helper::String::ReplaceAll(code, "#openBrowserDevTools", replacement);
  }

  void transpileBrowser::TranspileActivateDevConsole(std::string *code) {
    if (std::string::npos == code->find("#openBrowserDevConsole")) return;

    #if __linux__
      std::string replacement = "xdotool key ctrl+shift+k";
    #else
      std::string replacement =
          "osascript -e 'tell application \"System Events\" "
          "to keystroke \"k\" using {command down, option down}'\n";
    #endif

    replacement += "\nsleep 0.5";

    helper::String::ReplaceAll(code, "#openBrowserDevConsole", replacement);
  }

  void transpileBrowser::TranspileRunJs(std::string *code) {
    if (std::string::npos == code->find("#runJs")) return;

    std::string replacement =
        "#openBrowserDevConsole\n"
        "#copyPaste \"$1\"\n"
        "sleep 0.1\n"
        "#execDevConsole";

    std::regex exp(R"(#runJs \"(.*)\")");
    *code = std::regex_replace(*code, exp, replacement);
  }

  void transpileBrowser::TranspileExecDevConsole(std::string *code) {
    if (std::string::npos == code->find("#execDevConsole")) return;

    #if __linux__
      std::string replacement = "xdotool key ctrl+KP_Enter";
    #else
      std::string replacement =
          "osascript -e 'tell application \"System Events\" "
          "to key code 36 using command down'";
    #endif

    helper::String::ReplaceAll(code, "#execDevConsole", replacement);
  }

  void transpileBrowser::TranspileClearDevConsole(std::string *code) {
    if (std::string::npos == code->find("#clearDevConsole")) return;

    std::string replacement =
        "#openBrowserDevConsole\n"
        "#selectAll\n"
        "#hitBackspace\n";

    helper::String::ReplaceAll(code, "#clearDevConsole", replacement);
  }

  void transpileBrowser::TranspileFocusUrl(std::string *code) {
    if (std::string::npos == code->find("#focusBrowserURL")) return;

    #if __linux__
      std::string replacement = "xdotool key ctrl+l";
    #else
    std::string replacement =
        "osascript -e 'tell application \"System Events\" "
        "to keystroke \"l\" using command down'";
    #endif

    replacement += "\nsleep 0.1";

    helper::String::ReplaceAll(code, "#focusBrowserURL", replacement);
  }

  void transpileBrowser::TranspilePostFormData(std::string *code) {
    helper::String::ReplaceAll(
        code,
        "#getBrowserHtml",
          "(()=>{"
            "data=new FormData();"
            "data.set('html',document.documentElement.innerHTML);"
            "req=new XMLHttpRequest();"
            "req.open(\"POST\", 'http://localhost:8765', true);"
            "req.send(data);"
          "})()");
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
