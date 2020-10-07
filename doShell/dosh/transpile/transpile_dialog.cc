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

void transpileDialog::TranspileNotify(std::string *code) {
  if (std::string::npos == code->find("#notify ")) return;

  #if __linux__
    return helper::String::ReplaceAll(
        code,
        "#notify",
        "gxmessage -center -ontop ") > 0;
  #else
    // transpile: #notify $message
    std::string replacement = "osascript -e \"display notification \\\"$1\\\"\"";
    std::regex exp(R"(#notify (\$[a-zA-z]+))");

    *code = std::regex_replace(*code, exp, replacement);

    // transpile: #notify "message"
    replacement = "osascript -e 'display notification \"$1\"'";
    exp = (R"(#notify \"(.*)\")");
    *code = std::regex_replace(*code, exp, replacement);
  #endif
}

void transpileDialog::TranspileAlert(std::string *code) {
  if (std::string::npos == code->find("#alert ")) return;

  #if __linux__
    helper::String::ReplaceAll(
        code,
        "#alert",
        "gxmessage -center -ontop -bg red hello -title Alert ");
  #else
    std::string replacement = "osascript -e 'display alert \"$1\"'";
    std::regex exp(R"(#alert \"*(.*)\")");
    *code = std::regex_replace(*code, exp, replacement);
  #endif
}

void transpileDialog::TranspileConfirm(std::string *code) {
  if (std::string::npos == code->find("#confirm ")) return;

  #if __linux__
    helper::String::ReplaceAll(
        code,
        "#confirm ",
        "gxmessage -center -ontop -buttons \"Ok:1,Cancel:0\" ";
  #else
    std::regex exp(R"(#confirm \"*(.*)\")");

    std::string replacement =
        R"($(osascript -e 'display alert "$1" buttons {"Cancel", "Ok"}'))";

    *code = std::regex_replace(*code, exp, replacement);
  #endif
}

void transpileDialog::TranspilePrompt(std::string *code) {
  if (std::string::npos == code->find("#prompt ")) return;

  #if __linux__
    helper::String::ReplaceAll(
        code,
        "#confirm ",
        "gxmessage -center -ontop -buttons \"Ok:1,Cancel:0\" ");
  #else
   std::regex exp(R"(#prompt \"*(.*)\")");

   std::string replacement =
      "osascript -e 'set T to text returned of ("
        "display dialog \"$1\" "
        "buttons {"
            "\"Cancel\", "
            "\"OK\""
        "} "
        "default button \"OK\" "
        "default answer \"\")'";

   *code = std::regex_replace(*code, exp, replacement);
  #endif
}

}  // namespace doShell
