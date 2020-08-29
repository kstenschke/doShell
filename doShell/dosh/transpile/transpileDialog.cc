// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#include <doShell/dosh/transpile/transpileDialog.h>

namespace doShell {

void transpileDialog::Transpile(std::string *code, bool is_linux) {
  TranspileNotify(code, is_linux);
  TranspileAlert(code, is_linux);
  TranspileConfirm(code, is_linux);
  TranspilePrompt(code, is_linux);
}

bool transpileDialog::TranspileNotify(std::string *code,
                                               bool is_linux) {
  if (std::string::npos == code->find("#notify ")) return false;

  std::string replacement =
      is_linux
      ? "echo '$1' | xclip -sel clip #"
      : "osascript -e 'set the clipboard to \"$1\"'";

  std::regex exp(R"(#setClipboard \"(.*)\")");
  *code = std::regex_replace(*code, exp, replacement);

  return true;
}

bool transpileDialog::TranspileAlert(std::string *code,
                                               bool is_linux) {
  if (std::string::npos == code->find("#alert ")) return false;

  return true;
}

bool transpileDialog::TranspileConfirm(std::string *code,
                                               bool is_linux) {
  if (std::string::npos == code->find("#transpileConfirm ")) return false;


  return true;
}

bool transpileDialog::TranspilePrompt(std::string *code,
                                            bool is_linux) {
  if (std::string::npos == code->find("#transpilePrompt ")) return false;


  return true;
}

}  // namespace doShell
