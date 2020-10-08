// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#include <doShell/dosh/transpile/transpile_dialog.h>

namespace doShell {

transpileDialog::transpileDialog(std::string *code) {
  code_ = code;
}

void transpileDialog::Transpile(std::string *code) {
  auto *instance = new transpileDialog(code);

  instance
    ->TranspileNotify()
    ->TranspileAlert()
    ->TranspileConfirm()
    ->TranspilePrompt()
    ->TranspileSelect();

  delete instance;
}

transpileDialog* transpileDialog::TranspileNotify() {
  if (std::string::npos == code_->find("#notify ")) return this;

  #if __linux__
    return helper::String::ReplaceAll(
        code,
        "#notify",
        "gxmessage -center -ontop ") > 0;
  #else
    // transpile: #notify $message
    std::string replacement = "osascript -e \"display notification \\\"$1\\\"\"";
    std::regex exp(R"(#notify (\$[a-zA-z]+))");

    *code_ = std::regex_replace(*code_, exp, replacement);

    // transpile: #notify "message"
    replacement = "osascript -e 'display notification \"$1\"'";
    exp = (R"(#notify \"(.*)\")");
    *code_ = std::regex_replace(*code_, exp, replacement);
  #endif

  return this;
}

transpileDialog* transpileDialog::TranspileAlert() {
  if (std::string::npos == code_->find("#alert ")) return this;

  #if __linux__
    helper::String::ReplaceAll(
        code,
        "#alert",
        "gxmessage -center -ontop -bg red hello -title Alert ");
  #else
    std::regex exp(R"(#alert (\$.*))");
    std::string replacement = "osascript -e \"display alert \\\"$1\\\"\"";
    *code_ = std::regex_replace(*code_, exp, replacement);

    exp = (R"(#alert \"(.*)\")");
    replacement = "osascript -e 'display alert \"$1\"'";
    *code_ = std::regex_replace(*code_, exp, replacement);
  #endif

  return this;
}

transpileDialog* transpileDialog::TranspileConfirm() {
  if (std::string::npos == code_->find("#confirm ")) return this;

  #if __linux__
    helper::String::ReplaceAll(
        code,
        "#confirm ",
        "gxmessage -center -ontop -buttons \"Ok:1,Cancel:0\" ";
  #else
    std::regex exp(R"(#confirm \"*(.*)\")");

    std::string replacement =
        R"($(osascript -e 'display alert "$1" buttons {"Cancel", "Ok"}'))";

    *code_ = std::regex_replace(*code_, exp, replacement);
  #endif

  return this;
}

transpileDialog* transpileDialog::TranspilePrompt() {
  if (std::string::npos == code_->find("#prompt ")) return this;

  #if __linux__
    helper::String::ReplaceAll(
        code,
        "#confirm ",
        "gxmessage -center -ontop -buttons \"Ok:1,Cancel:0\" ");
  #else
   std::regex exp(R"(#prompt \"*(.*)\")");

   std::string replacement =
      "$("
        "osascript -e 'set T to text returned of ("
          "display dialog \"$1\" "
          "buttons {\"Cancel\", \"OK\"} "
          "default button \"OK\" "
          "default answer \"\""
        ")'"
      ")";

   *code_ = std::regex_replace(*code_, exp, replacement);
  #endif

  return this;
}

transpileDialog* transpileDialog::TranspileSelect() {
  if (std::string::npos == code_->find("#select ")) return this;

  #if __linux__
    helper::String::ReplaceAll(
        code,
        "#confirm ",
        "gxmessage -center -ontop -buttons \"Ok:1,Cancel:0\" ");
  #else
   std::regex exp(R"(#select \"(.*)\" (\{\".*\"(, )*\})+)");

   std::string replacement =
      "$(osascript <<EOF\n"
        "set doshOptions to $2\n"
        "set doshChoice to "
          "choose from list doshOptions "
          "with prompt \"$1\" "
          "default items {\"Apple\"}\n"
      "EOF)\n";

   *code_ = std::regex_replace(*code_, exp, replacement);
  #endif

  return this;
}

}  // namespace doShell
