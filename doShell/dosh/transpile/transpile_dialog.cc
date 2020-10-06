// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#include <doShell/dosh/transpile/transpile_dialog.h>

namespace doShell {

void transpileDialog::Transpile(std::string *code) {
  TranspileNotify(code);
  TranspileAlert(code);
  TranspileConfirm(code);
  TranspilePrompt(code);
}

bool transpileDialog::TranspileNotify(std::string *code) {
  if (std::string::npos == code->find("#notify ")) return false;

  #if __linux__
    return helper::String::ReplaceAll(
        code,
        "#notify",
        "gxmessage -center -ontop ") > 0;
  #endif

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

bool transpileDialog::TranspileAlert(std::string *code) {
  if (std::string::npos == code->find("#alert ")) return false;

  #if __linux__
    return helper::String::ReplaceAll(
        code,
        "#alert",
        "gxmessage -center -ontop -bg red hello -title Alert ") > 0;
  #endif

  std::string replacement = "osascript -e 'display alert \"$1\"'";
  std::regex exp(R"(#alert \"*(.*)\")");
  *code = std::regex_replace(*code, exp, replacement);

  return true;
}

bool transpileDialog::TranspileConfirm(std::string *code) {
  if (std::string::npos == code->find("#confirm ")) return false;

  #if __linux__
    return helper::String::ReplaceAll(
        code,
        "#confirm ",
        "gxmessage -center -ontop -buttons \"Ok:1,Cancel:0\" ") > 0;
  #endif

  std::regex exp(R"(#confirm \"*(.*)\")");

  std::string replacement =
      R"($(osascript -e 'display alert "$1" buttons {"Cancel", "Ok"}'))";

  *code = std::regex_replace(*code, exp, replacement);

  return true;
}

bool transpileDialog::TranspilePrompt(std::string *code) {
  if (std::string::npos == code->find("#prompt ")) return false;

  #if __linux__
    return helper::String::ReplaceAll(
        code,
        "#confirm ",
        "gxmessage -center -ontop -buttons \"Ok:1,Cancel:0\" ") > 0;
  #endif

  return helper::String::ReplaceAll(
      code,
      "#prompt ",
      "# // prompt ") > 0;
}

}  // namespace doShell
