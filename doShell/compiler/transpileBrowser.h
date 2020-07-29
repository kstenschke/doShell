// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#ifndef DOSHELL_COMPILER_TRANSPILEBROWSER_H_
#define DOSHELL_COMPILER_TRANSPILEBROWSER_H_

#include <doShell/helper/helper_string.h>

#include <string>

namespace doShell {
class transpileBrowser {
 public:
  static bool TranspileOpenUrlInNewBrowserTab(std::string *code, bool is_linux);

  static bool TranspileActivate(std::string *code, bool is_linux);
  static bool TranspileOpenNewTab(std::string *code, bool is_linux);
  static bool TranspileFocusUrl(std::string *code, bool is_linux);
};
}  // namespace doShell
#endif  // DOSHELL_COMPILER_TRANSPILEBROWSER_H_
