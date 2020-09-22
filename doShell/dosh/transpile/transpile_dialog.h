// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#ifndef DOSHELL_DOSH_TRANSPILE_TRANSPILE_DIALOG_H_
#define DOSHELL_DOSH_TRANSPILE_TRANSPILE_DIALOG_H_

#include <doShell/helper/helper_string.h>
#include <string>

namespace doShell {
class transpileDialog {
 public:
  static void Transpile(std::string *code, bool is_linux);

 private:
  static bool TranspileInfo(std::string *code, bool is_linux);
  static bool TranspileAlert(std::string *code, bool is_linux);
  static bool TranspileConfirm(std::string *code, bool is_linux);
  static bool TranspilePrompt(std::string *code, bool is_linux);
};
}  // namespace doShell

#endif  // DOSHELL_DOSH_TRANSPILE_TRANSPILE_DIALOG_H_
