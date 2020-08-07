// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#ifndef DOSHELL_DOSH_TRANSPILE_TRANSPILEBROWSER_H_
#define DOSHELL_DOSH_TRANSPILE_TRANSPILEBROWSER_H_

#include "transpileClipboard.h"
#include <doShell/helper/helper_string.h>
#include <string>

namespace doShell {
class transpileBrowser {
 public:
  static void Transpile(std::string *code, bool is_linux);

 private:
  static bool TranspileActivate(std::string *code, bool is_linux);

  static bool TranspileOpenNewTab(std::string *code, bool is_linux);
  static bool TranspileOpenUrlInNewBrowserTab(std::string *code, bool is_linux);

  static bool TranspileFocusUrl(std::string *code, bool is_linux);

  static bool TranspileRunJs(std::string *code, bool is_linux);
  static bool TranspileExecDevConsole(std::string *code, bool is_linux);
  static bool TranspileClearDevConsole(std::string *code, bool is_linux);
  static bool TranspileOpenBrowserDevTools(std::string *code, bool is_linux);
  static bool TranspileActivateDevConsole(std::string *code, bool is_linux);

  static bool TranspilePostFormData(std::string *code, bool is_linux);
};
}  // namespace doShell
#endif  // DOSHELL_DOSH_TRANSPILE_TRANSPILEBROWSER_H_
