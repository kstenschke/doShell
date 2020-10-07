// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#ifndef DOSHELL_DOSH_TRANSPILE_TRANSPILE_DIALOG_H_
#define DOSHELL_DOSH_TRANSPILE_TRANSPILE_DIALOG_H_

#include <doShell/helper/helper_string.h>
#include <string>

namespace doShell {
class transpileDialog {
 public:
  static void Transpile(std::string *code);

 private:
  static void TranspileNotify(std::string *code);
  static void TranspileAlert(std::string *code);
  static void TranspileConfirm(std::string *code);
  static void TranspilePrompt(std::string *code);
};
}  // namespace doShell

#endif  // DOSHELL_DOSH_TRANSPILE_TRANSPILE_DIALOG_H_
