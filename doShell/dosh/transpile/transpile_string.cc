// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#include <doShell/dosh/transpile/transpile_string.h>

#include <utility>

namespace doShell {

// Constructor
transpileString::transpileString(
    std::string *code, std::string path_binary, std::string from) {
  code_ = code;
  path_binary_ = std::move(path_binary);
  from_ = std::move(from);
}

void transpileString::Transpile(std::string *code,
                                const std::string &path_binary,
                                const std::string &from) {
  auto *instance = new transpileString(code, path_binary, from);

  instance->TranspileExtractBetween();

  if (!helper::String::Contains(*code, "_replace")) {
    delete instance;

    return;
  }

  instance
      ->TranspileReplaceAfter()
      ->TranspileReplaceAll()
      ->TranspileReplaceBefore()
      ->TranspileReplaceBetween()
      ->TranspileReplaceFirst()
      ->TranspileReplaceLast();

  delete instance;
}

transpileString* transpileString::TranspileExtractBetween() {
  std::string command = "_extractBetween" + from_ + " ";

  if (!helper::String::Contains(*code_, command)) return this;

  std::regex exp(command + "(.*) (.*) (.*)");
  std::string replacement =
      "$(" + path_binary_ + " " + command.substr(1) + "$1 $2 $3)";

  *code_ = std::regex_replace(*code_, exp, replacement);

  return this;
}

transpileString* transpileString::TranspileReplaceAfter() {
  std::string command = "_replaceAfter" + from_ + " ";

  if (!helper::String::Contains(*code_, command)) return this;

  std::regex exp(command + "(.*) (.*) (.*)");

  std::string replacement =
      "$(" + path_binary_ + " " + command.substr(1) + "$1 $2 $3)";

  *code_ = std::regex_replace(*code_, exp, replacement);

  return this;
}

transpileString* transpileString::TranspileReplaceAll() {
  std::string command = "_replaceAll" + from_ + " ";

  if (!helper::String::Contains(*code_, command)) return this;

  std::regex exp(command + "(.*) (.*) (.*)");

  std::string replacement =
      "$(" + path_binary_ + " " + command.substr(1) + "$1 $2 $3)";

  *code_ = std::regex_replace(*code_, exp, replacement);

  return this;
}

transpileString* transpileString::TranspileReplaceBefore() {
  std::string command = "_replaceBefore" + from_ + " ";

  if (!helper::String::Contains(*code_, command)) return this;

  std::regex exp(command + "(.*) (.*) (.*)");

  std::string replacement =
      "$(" + path_binary_ + " " + command.substr(1) + "$1 $2 $3)";

  *code_ = std::regex_replace(*code_, exp, replacement);

  return this;
}

transpileString* transpileString::TranspileReplaceBetween() {
  std::string command = "_replaceBetween" + from_ + " ";

  if (!helper::String::Contains(*code_, command)) return this;

  std::regex exp(command + "(.*) (.*) (.*) (.*)");

  std::string replacement =
      "$(" + path_binary_ + " " + command.substr(1) + "$1 $2 $3 $4)";

  *code_ = std::regex_replace(*code_, exp, replacement);

  return this;
}

transpileString* transpileString::TranspileReplaceFirst() {
  std::string command = "_replaceFirst" + from_ + " ";

  if (!helper::String::Contains(*code_, command)) return this;

  std::regex exp(command + "(.*) (.*) (.*)");

  std::string replacement =
      "$(" + path_binary_ + " " + command.substr(1) + "$1 $2 $3)";

  *code_ = std::regex_replace(*code_, exp, replacement);

  return this;
}

transpileString* transpileString::TranspileReplaceLast() {
  std::string command = "_replaceLast" + from_ + " ";

  if (!helper::String::Contains(*code_, command)) return this;

  std::regex exp(command + "(.*) (.*) (.*)");

  std::string replacement =
      "$(" + path_binary_ + " " + command.substr(1) + "$1 $2 $3)";

  *code_ = std::regex_replace(*code_, exp, replacement);

  return this;
}

}  // namespace doShell
