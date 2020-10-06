// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#include <doShell/dosh/transpile/transpile_string.h>

#include <utility>

namespace doShell {

transpileString::transpileString(std::string path_binary, std::string from) {
  path_binary_ = std::move(path_binary);
  from_ = std::move(from);
}

void transpileString::Transpile(std::string *code,
                                const std::string &path_binary,
                                const std::string &from) {
  auto *instance = new transpileString(path_binary, from);

  instance->TranspileExtractBetween(code);

  if (!helper::String::Contains(*code, "#replace")) {
    delete instance;

    return;
  }

  instance
      ->TranspileReplaceAfter(code)
      ->TranspileReplaceAll(code)
      ->TranspileReplaceBefore(code)
      ->TranspileReplaceBetween(code)
      ->TranspileReplaceFirst(code)
      ->TranspileReplaceLast(code);

  delete instance;
}

transpileString* transpileString::TranspileExtractBetween(std::string *code) {
  std::string command = "#extractBetween" + from_ + " ";

  if (!helper::String::Contains(*code, command)) return this;

  std::regex exp(command + "(.*) (.*) (.*)");
  std::string replacement =
      "$(" + path_binary_ + " " + command.substr(1) + "$1 $2 $3)";

  *code = std::regex_replace(*code, exp, replacement);

  return this;
}

transpileString* transpileString::TranspileReplaceAfter(std::string *code) {
  std::string command = "#replaceAfter" + from_ + " ";

  if (!helper::String::Contains(*code, command)) return this;

  std::regex exp(command + "(.*) (.*) (.*)");
  std::string replacement = "$(" + path_binary_ + " " + command.substr(1) + "$1 $2 $3)";

  *code = std::regex_replace(*code, exp, replacement);

  return this;
}

transpileString* transpileString::TranspileReplaceAll(std::string *code) {
  std::string command = "#replaceAll" + from_ + " ";

  if (!helper::String::Contains(*code, command)) return this;

  std::regex exp(command + "(.*) (.*) (.*)");
  std::string replacement = "$(" + path_binary_ + " " + command.substr(1) + "$1 $2 $3)";

  *code = std::regex_replace(*code, exp, replacement);

  return this;
}

transpileString* transpileString::TranspileReplaceBefore(std::string *code) {
  std::string command = "#replaceBefore" + from_ + " ";

  if (!helper::String::Contains(*code, command)) return this;

  std::regex exp(command + "(.*) (.*) (.*)");
  std::string replacement = "$(" + path_binary_ + " " + command.substr(1) + "$1 $2 $3)";

  *code = std::regex_replace(*code, exp, replacement);

  return this;
}

transpileString* transpileString::TranspileReplaceBetween(std::string *code) {
  std::string command = "#replaceBetween" + from_ + " ";

  if (!helper::String::Contains(*code, command)) return this;

  std::regex exp(command + "(.*) (.*) (.*) (.*)");
  std::string replacement = "$(" + path_binary_ + " " + command.substr(1) + "$1 $2 $3 $4)";

  *code = std::regex_replace(*code, exp, replacement);

  return this;
}

transpileString* transpileString::TranspileReplaceFirst(std::string *code) {
  std::string command = "#replaceFirst" + from_ + " ";

  if (!helper::String::Contains(*code, command)) return this;

  std::regex exp(command + "(.*) (.*) (.*)");
  std::string replacement = "$(" + path_binary_ + " " + command.substr(1) + "$1 $2 $3)";

  *code = std::regex_replace(*code, exp, replacement);

  return this;
}

transpileString* transpileString::TranspileReplaceLast(std::string *code) {
  std::string command = "#replaceLast" + from_ + " ";

  if (!helper::String::Contains(*code, command)) return this;

  std::regex exp(command + "(.*) (.*) (.*)");
  std::string replacement = "$(" + path_binary_ + " " + command.substr(1) + "$1 $2 $3)";

  *code = std::regex_replace(*code, exp, replacement);

  return this;
}

}  // namespace doShell
