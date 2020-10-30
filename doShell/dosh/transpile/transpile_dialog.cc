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
    helper::String::ReplaceAll(code_, "#notify", "notify-send ");
  #else
    // transpile: #notify $message
    std::string replacement =
        "osascript -e \"display notification \\\"$1\\\"\"";

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
    std::regex exp(R"(#alert (\$.*))");
    std::string replacement = "zenity --warning --no-wrap --text=\"$1\" ::MUTE::";
    *code_ = std::regex_replace(*code_, exp, replacement);

    exp = (R"(#alert \"(.*)\")");
    *code_ = std::regex_replace(*code_, exp, replacement);
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

  std::regex exp(R"(#confirm \"*(.*)\")");

  #if __linux__
    std::string replacement =
        "$("
          "zenity --question --no-wrap --text=\"$1\" ::MUTE:: ; "
          "if [ \"$?\" -eq 0 ]; then echo 'Ok'; else echo 'Cancel'; fi"
        ")";

    *code_ = std::regex_replace(*code_, exp, replacement);
  #else
    std::string replacement =
        R"($(osascript -e 'display alert "$1" buttons {"Cancel", "Ok"}'))";

    *code_ = std::regex_replace(*code_, exp, replacement);
  #endif

  return this;
}

transpileDialog* transpileDialog::TranspilePrompt() {
  if (std::string::npos == code_->find("#prompt ")) return this;

  std::regex exp(R"(#prompt \"*(.*)\")");

  #if __linux__
    std::string replacement =
        "$("
          "zenity --entry --text=\"$1\" ::MUTE_2::"
        ")";

    *code_ = std::regex_replace(*code_, exp, replacement);
  #else
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
    // step 1: transform into zenity list command
    std::regex exp(R"(#select \"(.*)\" \{(\".*\"(, )*)+\})");

    std::string replacement =
        "$("
          "column_names=(--column=Item); "
          "row=($2); "
          "zenity --width=520 --height=300 "
          "--list --title=\"list\" "
          "\"${column_names[@]}\" \"${row[@]}\""
        ")";

    *code_ = std::regex_replace(*code_, exp, replacement);

    // step 2: remove undesired commas between row items
    // TODO(kay) implement

  #else
    std::regex exp(R"(#select \"(.*)\" (\{\".*\"(, )*\})+)");

    std::string replacement =
       "$(osascript <<EOF\n"
         "set doshOptions to $2\n"
         "set doshChoice to "
           "choose from list doshOptions "
           "with prompt \"$1\" \n"
//           "default items {\"Apple\"}\n"
       "EOF)\n";

    *code_ = std::regex_replace(*code_, exp, replacement);
  #endif

  return this;
}

}  // namespace doShell
