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
                                bool is_linux,
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
  if (!helper::String::Contains(*code, "#extractBetween" + from_)) return this;

  std::regex exp2("#extractBetween" + from_ + " (.*) (.*) (.*)");
  std::string replacement = "$(" + path_binary_ + " extractBetween" + from_ + " $1 $2 $3);";

  *code = std::regex_replace(*code, exp2, replacement);

  return this;
}

transpileString* transpileString::TranspileReplaceAfter(std::string *code) {
  if (!helper::String::Contains(*code, "#replaceAfter" + from_)) return this;

  std::regex exp2("#replaceAfter" + from_ + " (.*) (.*) (.*)");
  std::string replacement = "$(" + path_binary_ + " replaceAfter" + from_ + " $1 $2 $3);";

  *code = std::regex_replace(*code, exp2, replacement);

  return this;
}

transpileString* transpileString::TranspileReplaceAll(std::string *code) {
  if (!helper::String::Contains(*code, "#replaceAll" + from_)) return this;

  std::regex exp2("#replaceAll" + from_ + " (.*) (.*) (.*)");
  std::string replacement = "$(" + path_binary_ + " replaceAll" + from_ + " $1 $2 $3);";

  *code = std::regex_replace(*code, exp2, replacement);

  return this;
}

transpileString* transpileString::TranspileReplaceBefore(std::string *code) {
  if (!helper::String::Contains(*code, "#replaceBefore" + from_)) return this;

  std::regex exp2("#replaceBefore" + from_ + " (.*) (.*) (.*)");
  std::string replacement = "$(" + path_binary_ + " replaceBefore" + from_ + " $1 $2 $3);";

  *code = std::regex_replace(*code, exp2, replacement);

  return this;
}

transpileString* transpileString::TranspileReplaceBetween(std::string *code) {
  if (!helper::String::Contains(*code, "#replaceBetween" + from_)) return this;

  std::regex exp2("#replaceBetween" + from_ + " (.*) (.*) (.*) (.*)");
  std::string replacement = "$(" + path_binary_ + " replaceBetween" + from_ + " $1 $2 $3 $4);";

  *code = std::regex_replace(*code, exp2, replacement);

  return this;
}

transpileString* transpileString::TranspileReplaceFirst(std::string *code) {
  if (!helper::String::Contains(*code, "#replaceFirst" + from_)) return this;

  std::regex exp2("#replaceFirst" + from_ + " (.*) (.*) (.*)");
  std::string replacement = "$(" + path_binary_ + " replaceFirst" + from_ + " $1 $2 $3);";

  *code = std::regex_replace(*code, exp2, replacement);

  return this;
}

transpileString* transpileString::TranspileReplaceLast(std::string *code) {
  if (!helper::String::Contains(*code, "#replaceLast" + from_)) return this;

  std::regex exp2("#replaceLast" + from_ + " (.*) (.*) (.*)");
  std::string replacement = "$(" + path_binary_ + " replaceLast" + from_ + " $1 $2 $3);";

  *code = std::regex_replace(*code, exp2, replacement);

  return this;
}

}  // namespace doShell
