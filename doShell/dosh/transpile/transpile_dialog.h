// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#ifndef DOSHELL_DOSH_TRANSPILE_TRANSPILE_DIALOG_H_
#define DOSHELL_DOSH_TRANSPILE_TRANSPILE_DIALOG_H_

#include <doShell/helper/helper_string.h>
#include <string>

namespace doShell {
class transpileDialog {
 public:
  explicit transpileDialog(std::string *code);
  static void Transpile(std::string *code);

 private:
  std::string *code_;

  transpileDialog* TranspileNotify();
  transpileDialog* TranspileAlert();
  transpileDialog* TranspileConfirm();
  transpileDialog* TranspilePrompt();
  transpileDialog* TranspileSelect();

  void RemoveCommasBetweenRowItems() const;
};
}  // namespace doShell

#endif  // DOSHELL_DOSH_TRANSPILE_TRANSPILE_DIALOG_H_
