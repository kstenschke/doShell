// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#ifndef DOSHELL_DOSH_TRANSPILE_TRANSPILE_BROWSER_H_
#define DOSHELL_DOSH_TRANSPILE_TRANSPILE_BROWSER_H_

#include <doShell/dosh/transpile/transpile_clipboard.h>
#include <doShell/helper/helper_string.h>
#include <string>

namespace doShell {
class transpileBrowser {
 public:
  explicit transpileBrowser(std::string *code);
  static void Transpile(std::string *code);

 private:
  std::string *code_;
  std::string *browser_;

  // Transpile wrapper-commands resolving to multiple other doShell commands
  transpileBrowser* TranspileComboCommands();

  transpileBrowser* TranspileActivate();

  transpileBrowser* TranspileOpenNewTab();
  transpileBrowser* TranspileOpenUrlInNewBrowserTab();
  transpileBrowser* TranspileCloseTab();

  transpileBrowser* TranspileOpenBrowserSource();

  transpileBrowser* TranspileFocusUrl();

  transpileBrowser* TranspileRunJs();
  transpileBrowser* TranspileExecDevConsole();
  transpileBrowser* TranspileClearDevConsole();
  transpileBrowser* TranspileOpenBrowserDevTools();
  transpileBrowser* TranspileActivateDevConsole();

  transpileBrowser* TranspilePostFormData();
};
}  // namespace doShell
#endif  // DOSHELL_DOSH_TRANSPILE_TRANSPILE_BROWSER_H_
