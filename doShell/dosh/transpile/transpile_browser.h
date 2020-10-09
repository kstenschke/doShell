// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#ifndef DOSHELL_DOSH_TRANSPILE_TRANSPILE_BROWSER_H_
#define DOSHELL_DOSH_TRANSPILE_TRANSPILE_BROWSER_H_

#include "transpile_clipboard.h"
#include <doShell/helper/helper_string.h>
#include <string>

namespace doShell {
class transpileBrowser {
 public:
  explicit transpileBrowser(std::string *code);
  static void Transpile(std::string *code);

 private:
  std::string *code_;

  transpileBrowser* TranspileActivate();

  transpileBrowser* TranspileOpenNewTab();
  transpileBrowser* TranspileOpenUrlInNewBrowserTab();

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
