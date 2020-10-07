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
  static void Transpile(std::string *code);

 private:
  static void TranspileActivate(std::string *code);

  static void TranspileOpenNewTab(std::string *code);
  static void TranspileOpenUrlInNewBrowserTab(std::string *code);

  static void TranspileFocusUrl(std::string *code);

  static void TranspileRunJs(std::string *code);
  static void TranspileExecDevConsole(std::string *code);
  static void TranspileClearDevConsole(std::string *code);
  static void TranspileOpenBrowserDevTools(std::string *code);
  static void TranspileActivateDevConsole(std::string *code);

  static void TranspilePostFormData(std::string *code);
};
}  // namespace doShell
#endif  // DOSHELL_DOSH_TRANSPILE_TRANSPILE_BROWSER_H_
