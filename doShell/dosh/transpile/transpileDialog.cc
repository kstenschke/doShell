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

bool transpileDialog::TranspileNotify(std::string *code, bool is_linux) {
  if (std::string::npos == code->find("#notify ")) return false;

  if (is_linux) {
    return helper::String::ReplaceAll(
        code,
        "#notify",
        "gxmessage ") > 0;
  }

  std::string replacement = "osascript -e 'display notification \"$1\"'";
  std::regex exp(R"(#alert \"*(.*)\"*)");
  *code = std::regex_replace(*code, exp, replacement);

  return true;
}

bool transpileDialog::TranspileAlert(std::string *code, bool is_linux) {
  if (std::string::npos == code->find("#alert ")) return false;

  if (is_linux) {
    return helper::String::ReplaceAll(
        code,
        "#alert",
        "gxmessage -bg red hello -title Alert ") > 0;
  }

  std::string replacement =
      "osascript -e 'display dialog \"$1\" with icon caution '";

  std::regex exp(R"(#alert \"*(.*)\"*)");
  *code = std::regex_replace(*code, exp, replacement);

  return true;
}

bool transpileDialog::TranspileConfirm(std::string *code, bool is_linux) {
  if (std::string::npos == code->find("#transpileConfirm ")) return false;


  return true;
}

bool transpileDialog::TranspilePrompt(std::string *code, bool is_linux) {
  if (std::string::npos == code->find("#transpilePrompt ")) return false;


  return true;
}

}  // namespace doShell
