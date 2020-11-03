// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#include <doShell/dosh/transpile/transpile_dialog.h>
#include <iostream>

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
  if (std::string::npos == code_->find("_notify ")) return this;

  #if __linux__
    helper::String::ReplaceAll(code_, "_notify", "notify-send ");
  #else
    // transpile: _notify $message
    std::string replacement =
        "osascript -e \"display notification \\\"$1\\\"\"";

    std::regex exp(R"(_notify (\$[a-zA-z]+))");

    *code_ = std::regex_replace(*code_, exp, replacement);

    // transpile: _notify "message"
    replacement = "osascript -e 'display notification \"$1\"'";
    exp = (R"(_notify \"(.*)\")");
    *code_ = std::regex_replace(*code_, exp, replacement);
  #endif

  return this;
}

transpileDialog* transpileDialog::TranspileAlert() {
  if (std::string::npos == code_->find("_alert ")) return this;

  #if __linux__
    std::regex exp(R"(_alert (\$.*))");

    std::string replacement =
        "zenity --warning --no-wrap --text=\"$1\" ::MUTE::";

    *code_ = std::regex_replace(*code_, exp, replacement);

    exp = (R"(_alert \"(.*)\")");
    *code_ = std::regex_replace(*code_, exp, replacement);
  #else
    std::regex exp(R"(_alert (\$.*))");
    std::string replacement = "osascript -e \"display alert \\\"$1\\\"\"";
    *code_ = std::regex_replace(*code_, exp, replacement);

    exp = (R"(_alert \"(.*)\")");
    replacement = "osascript -e 'display alert \"$1\"'";
    *code_ = std::regex_replace(*code_, exp, replacement);
  #endif

  return this;
}

transpileDialog* transpileDialog::TranspileConfirm() {
  if (std::string::npos == code_->find("_confirm ")) return this;

  std::regex exp(R"(_confirm \"*(.*)\")");

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
  if (std::string::npos == code_->find("_prompt ")) return this;

  std::regex exp(R"(_prompt \"*(.*)\")");

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
  if (std::string::npos == code_->find("_select ")) return this;

  #if __linux__
    // step 1: remove undesired commas between row items
    // (needed only for mac os / appleScript)
    RemoveCommasBetweenRowItems();

    // step 2: transform into zenity list command
    std::regex exp1(R"(_select \"(.*)\" \{(\".*\"( )*)+\})");

    std::string replacement =
        "$("
          "column_names=(--column=Item); "
          "row=($2); "
          "zenity --width=520 --height=300 "
          "--list --title=\"list\" "
          "\"${column_names[@]}\" \"${row[@]}\" ::MUTE_2::"
        ")";

    *code_ = std::regex_replace(*code_, exp1, replacement);
#else
    std::regex exp(R"(_select \"(.*)\" (\{\".*\"(, )*\})+)");

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

// transform lines like: _select "Take your pick:" {"Apple", "Banana", "Orange"}
//                 into: _select "Take your pick:" {"Apple" "Banana" "Orange"}
void transpileDialog::RemoveCommasBetweenRowItems() const {
  int offset_select = 0;
  auto len_code = code_->length();

  do {
    offset_select = code_->find("_select ", offset_select + 8);

    if (offset_select == std::string::npos || offset_select >= len_code) break;

    auto offset_in_items = code_->find("{", offset_select);
    auto offset_newline = code_->find("\n", offset_select + 1);

    if (offset_in_items != std::string::npos) {
      ++offset_in_items;

      char ch = '{';
      char ch_prev;

      bool is_within_item = false;

      do {
        ch_prev = ch;
        ch = code_->operator[](offset_in_items);

        if (ch == '"' && ch_prev != '\\')
          is_within_item = !is_within_item;
        else if (!is_within_item && ch == ',')
          code_->operator[](offset_in_items) = ' ';

        ++offset_in_items;
      } while (
          ch != '\n' && offset_in_items < offset_newline);
    }
  } while (offset_select != std::string::npos && offset_select >= len_code);
}

}  // namespace doShell
