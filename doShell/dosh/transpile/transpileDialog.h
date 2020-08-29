// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#ifndef DOSHELL_DOSH_TRANSPILE_TRANSPILEDIALOG_H_
#define DOSHELL_DOSH_TRANSPILE_TRANSPILEDIALOG_H_

#include <doShell/helper/helper_string.h>
#include <string>

namespace doShell {
class transpileDialog {
 public:
  static void Transpile(std::string *code, bool is_linux);

 private:
  static bool TranspileNotify(std::string *code, bool is_linux);
  static bool TranspileAlert(std::string *code, bool is_linux);
  static bool TranspileConfirm(std::string *code, bool is_linux);
  static bool TranspilePrompt(std::string *code, bool is_linux);
};
}  // namespace doShell

#endif  // DOSHELL_DOSH_TRANSPILE_TRANSPILECLIPBOARD_H_
