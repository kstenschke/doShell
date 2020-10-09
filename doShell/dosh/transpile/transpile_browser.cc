// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#include <doShell/dosh/transpile/transpile_browser.h>

namespace doShell {
transpileBrowser::transpileBrowser(std::string *code) {
  code_ = code;  
}

void transpileBrowser::Transpile(std::string *code) {
  auto *instance = new transpileBrowser(code);

  instance
    ->TranspileActivate()
    ->TranspileOpenUrlInNewBrowserTab()
    ->TranspileOpenNewTab()
    ->TranspileOpenBrowserSource()
    ->TranspileFocusUrl()
    ->TranspileOpenBrowserDevTools()
    ->TranspileActivateDevConsole()
    ->TranspileRunJs()
    ->TranspileExecDevConsole()
    ->TranspileClearDevConsole()
    ->TranspileCloseTab();

  delete instance;
}

transpileBrowser* transpileBrowser::TranspileActivate() {
  if (std::string::npos == code_->find("#activateBrowser")) return this;

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

  helper::String::ReplaceAll(code_, "#activateBrowser", replacement);

  return this;
}

transpileBrowser* transpileBrowser::TranspileOpenNewTab() {
  if (std::string::npos == code_->find("#openNewBrowserTab")) return this;

#if __linux__
  std::string replacement = "xdotool key ctrl+t";
#else
  std::string replacement =
      "osascript -e 'tell application \"System Events\" "
          "to keystroke \"t\" using command down'";
#endif

  replacement += "\nsleep 0.3";

  helper::String::ReplaceAll(code_, "#openNewBrowserTab", replacement);

  return this;
}

transpileBrowser* transpileBrowser::TranspileCloseTab() {
  if (std::string::npos == code_->find("#closeBrowserTab")) return this;

#if __linux__
  std::string replacement = "xdotool key ctrl+w";
#else
  std::string replacement =
      "osascript -e 'tell application \"System Events\" "
          "to keystroke \"w\" using command down'";
#endif

  replacement += "\nsleep 0.2";

  helper::String::ReplaceAll(code_, "#closeBrowserTab", replacement);

  return this;
}

transpileBrowser* transpileBrowser::TranspileOpenBrowserSource() {
  if (std::string::npos == code_->find("#openBrowserSource")) return this;

#if __linux__
  std::string replacement = "xdotool key ctrl+u";
#else
  std::string replacement =
      "osascript -e 'tell application \"System Events\" "
          "to keystroke \"u\" using command down'";
#endif

  replacement += "\nsleep 0.1";

  helper::String::ReplaceAll(code_, "#openBrowserSource", replacement);

  return this;
}

transpileBrowser* transpileBrowser::TranspileOpenUrlInNewBrowserTab() {
  if (std::string::npos == code_->find("#openUrlInNewBrowserTab ")) return this;

  std::string replacement =
      "#openNewBrowserTab\n"
      "#focusBrowserURL\n"
      "#copyPaste \"$1/\"\n"
      "sleep 0.2\n"
      "#hitEnter\n"
      "sleep 0.5\n";

  std::regex exp(R"(#openUrlInNewBrowserTab \"(.*)\")");
  *code_ = std::regex_replace(*code_, exp, replacement);

//    transpileClipboard::Transpile(code_, is_linux);

  return this;
}

transpileBrowser* transpileBrowser::TranspileOpenBrowserDevTools() {
  if (std::string::npos == code_->find("#openBrowserDevTools")) return this;

  #if __linux__
    std::string replacement = "xdotool key F12";
  #else
  std::string replacement =
      "osascript -e 'tell application \"System Events\" "
      "to keystroke \"F12\"'";
  #endif

  replacement += "\nsleep 0.5";

  helper::String::ReplaceAll(code_, "#openBrowserDevTools", replacement);

  return this;
}

transpileBrowser* transpileBrowser::TranspileActivateDevConsole() {
  if (std::string::npos == code_->find("#openBrowserDevConsole")) return this;

  #if __linux__
    std::string replacement = "xdotool key ctrl+shift+k";
  #else
    std::string replacement =
        "osascript -e 'tell application \"System Events\" "
        "to keystroke \"k\" using {command down, option down}'\n";
  #endif

  replacement += "\nsleep 0.5";

  helper::String::ReplaceAll(code_, "#openBrowserDevConsole", replacement);

  return this;
}

transpileBrowser* transpileBrowser::TranspileRunJs() {
  if (std::string::npos == code_->find("#runJs")) return this;

  std::string replacement =
      "#openBrowserDevConsole\n"
      "#copyPaste \"$1\"\n"
      "sleep 0.1\n"
      "#execDevConsole";

  std::regex exp(R"(#runJs \"(.*)\")");
  *code_ = std::regex_replace(*code_, exp, replacement);

  return this;
}

transpileBrowser* transpileBrowser::TranspileExecDevConsole() {
  if (std::string::npos == code_->find("#execDevConsole")) return this;

  #if __linux__
    std::string replacement = "xdotool key ctrl+KP_Enter";
  #else
    std::string replacement =
        "osascript -e 'tell application \"System Events\" "
        "to key code 36 using command down'";
  #endif

  helper::String::ReplaceAll(code_, "#execDevConsole", replacement);

  return this;
}

transpileBrowser* transpileBrowser::TranspileClearDevConsole() {
  if (std::string::npos == code_->find("#clearDevConsole")) return this;

  std::string replacement =
      "#openBrowserDevConsole\n"
      "#selectAll\n"
      "#hitBackspace\n";

  helper::String::ReplaceAll(code_, "#clearDevConsole", replacement);

  return this;
}

transpileBrowser* transpileBrowser::TranspileFocusUrl() {
  if (std::string::npos == code_->find("#focusBrowserURL")) return this;

  #if __linux__
    std::string replacement = "xdotool key ctrl+l";
  #else
  std::string replacement =
      "osascript -e 'tell application \"System Events\" "
      "to keystroke \"l\" using command down'";
  #endif

  replacement += "\nsleep 0.1";

  helper::String::ReplaceAll(code_, "#focusBrowserURL", replacement);

  return this;
}

transpileBrowser* transpileBrowser::TranspilePostFormData() {
  helper::String::ReplaceAll(
      code_,
      "#getBrowserHtml",
        "(()=>{"
          "data=new FormData();"
          "data.set('html',document.documentElement.innerHTML);"
          "req=new XMLHttpRequest();"
          "req.open(\"POST\", 'http://localhost:8765', true);"
          "req.send(data);"
        "})()");

  return this;
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
