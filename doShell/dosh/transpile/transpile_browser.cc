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

  bool transpileBrowser::TranspileActivate(std::string *code) {
    if (std::string::npos == code->find("#activateBrowser")) return false;

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

    return helper::String::ReplaceAll(
        code, "#activateBrowser", replacement) > 0;
  }


  bool transpileBrowser::TranspileOpenUrlInNewBrowserTab(std::string *code) {
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

  bool transpileBrowser::TranspileOpenNewTab(std::string *code) {
    if (std::string::npos == code->find("#openNewBrowserTab")) return false;

    #if __linux__
      std::string replacement = "xdotool key ctrl+t";
    #else
      std::string replacement =
          "osascript -e 'tell application \"System Events\" "
          "to keystroke \"t\" using command down'";
    #endif

    replacement += "\nsleep 0.1";

    return helper::String::ReplaceAll(
        code, "#openNewBrowserTab", replacement) > 0;
  }

  bool transpileBrowser::TranspileOpenBrowserDevTools(std::string *code) {
    if (std::string::npos == code->find("#openBrowserDevTools")) return false;

    #if __linux__
      std::string replacement = "xdotool key F12";
    #else
    std::string replacement =
        "osascript -e 'tell application \"System Events\" "
        "to keystroke \"F12\"'";
    #endif

    replacement += "\nsleep 0.5";

    return helper::String::ReplaceAll(
        code, "#openBrowserDevTools", replacement) > 0;
  }

  bool transpileBrowser::TranspileActivateDevConsole(std::string *code) {
    if (std::string::npos == code->find("#openBrowserDevConsole")) return false;

    #if __linux__
      std::string replacement = "xdotool key ctrl+shift+k";
    #else
      std::string replacement =
          "osascript -e 'tell application \"System Events\" "
          "to keystroke \"k\" using {command down, option down}'\n";
    #endif

    replacement += "\nsleep 0.5";

    return helper::String::ReplaceAll(
        code, "#openBrowserDevConsole", replacement) > 0;
  }

  bool transpileBrowser::TranspileRunJs(std::string *code) {
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

  bool transpileBrowser::TranspileExecDevConsole(std::string *code) {
    if (std::string::npos == code->find("#execDevConsole")) return false;

    #if __linux__
      std::string replacement = "xdotool key ctrl+KP_Enter";
    #else
      std::string replacement =
          "osascript -e 'tell application \"System Events\" "
          "to key code 36 using command down'";
    #endif

    return helper::String::ReplaceAll(
        code, "#execDevConsole", replacement) > 0;
  }

  bool transpileBrowser::TranspileClearDevConsole(std::string *code) {
    if (std::string::npos == code->find("#clearDevConsole")) return false;

    std::string replacement =
        "#openBrowserDevConsole\n"
        "#selectAll\n"
        "#hitBackspace\n";

    return helper::String::ReplaceAll(
        code, "#clearDevConsole", replacement) > 0;
  }

  bool transpileBrowser::TranspileFocusUrl(std::string *code) {
    if (std::string::npos == code->find("#focusBrowserURL")) return false;

    #if __linux__
      std::string replacement = "xdotool key ctrl+l";
    #else
    std::string replacement =
        "osascript -e 'tell application \"System Events\" "
        "to keystroke \"l\" using command down'";
    #endif

    replacement += "\nsleep 0.1";

    return helper::String::ReplaceAll(
        code, "#focusBrowserURL", replacement) > 0;
  }

  bool transpileBrowser::TranspilePostFormData(std::string *code) {
    return helper::String::ReplaceAll(
        code,
        "#getBrowserHtml",
          "(()=>{"
            "data=new FormData();"
            "data.set('html',document.documentElement.innerHTML);"
            "req=new XMLHttpRequest();"
            "req.open(\"POST\", 'http://localhost:8765', true);"
            "req.send(data);"
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
