// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#include <doShell/dosh/transpile/transpile_dialog.h>

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
        "gxmessage -center -ontop ") > 0;
  }

  // transpile: #notify $message
  std::string replacement = "osascript -e \"display notification \\\"$1\\\"\"";
  std::regex exp(R"(#notify (\$[a-zA-z]+))");

  *code = std::regex_replace(*code, exp, replacement);

  // transpile: #notify "message"
  replacement = "osascript -e 'display notification \"$1\"'";
  exp = (R"(#notify \"(.*)\")");
  *code = std::regex_replace(*code, exp, replacement);

  return true;
}

bool transpileDialog::TranspileAlert(std::string *code, bool is_linux) {
  if (std::string::npos == code->find("#alert ")) return false;

  if (is_linux) {
    return helper::String::ReplaceAll(
        code,
        "#alert",
        "gxmessage -center -ontop -bg red hello -title Alert ") > 0;
  }

  std::string replacement = "osascript -e 'display alert \"$1\"'";
  std::regex exp(R"(#alert \"*(.*)\")");
  *code = std::regex_replace(*code, exp, replacement);

  return true;
}

bool transpileDialog::TranspileConfirm(std::string *code, bool is_linux) {
  if (std::string::npos == code->find("#confirm ")) return false;

  if (is_linux) {
    return helper::String::ReplaceAll(
        code,
        "#confirm ",
        "gxmessage -center -ontop -buttons \"Ok:1,Cancel:0\" ") > 0;
  }

  std::regex exp(R"(#confirm \"*(.*)\")");

  std::string replacement =
      R"($(osascript -e 'display alert "$1" buttons {"Cancel", "Ok"}'))";

  *code = std::regex_replace(*code, exp, replacement);

  return true;
}

bool transpileDialog::TranspilePrompt(std::string *code, bool is_linux) {
  if (std::string::npos == code->find("#prompt ")) return false;

  // TODO(kay) implement

  return helper::String::ReplaceAll(
      code,
      "#prompt ",
      "# // prompt ") > 0;
}

}  // namespace doShell
