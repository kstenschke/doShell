// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#include <doShell/dosh/transpile/transpile_string.h>

#include <utility>

namespace doShell {

transpileString::transpileString(std::string path_binary) {
  path_binary_ = std::move(path_binary);
}

void transpileString::Transpile(
    std::string *code, bool is_linux, std::string path_binary) {
  auto *instance = new transpileString(std::move(path_binary));

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
  if (!helper::String::Contains(*code, "#extractBetween")) return this;

  std::regex exp2("#extractBetween (.*) (.*) (.*)");
  std::string replacement = "$(" + path_binary_ + " extractBetween $1 $2 $3);";

  *code = std::regex_replace(*code, exp2, replacement);

  return this;
}

transpileString* transpileString::TranspileReplaceAfter(std::string *code) {
  if (!helper::String::Contains(*code, "#replaceAfter")) return this;

  std::regex exp2("#replaceAfter (.*) (.*) (.*)");
  std::string replacement = "$(" + path_binary_ + " replaceAfter $1 $2 $3);";

  *code = std::regex_replace(*code, exp2, replacement);

  return this;
}

transpileString* transpileString::TranspileReplaceAll(std::string *code) {
  if (!helper::String::Contains(*code, "#replaceAll")) return this;

  std::regex exp2("#replaceAll (.*) (.*) (.*)");
  std::string replacement = "$(" + path_binary_ + " replaceAll $1 $2 $3);";

  *code = std::regex_replace(*code, exp2, replacement);

  return this;
}

transpileString* transpileString::TranspileReplaceBefore(std::string *code) {
  if (!helper::String::Contains(*code, "#replaceBefore")) return this;

  std::regex exp2("#replaceBefore (.*) (.*) (.*)");
  std::string replacement = "$(" + path_binary_ + " replaceBefore $1 $2 $3);";

  *code = std::regex_replace(*code, exp2, replacement);

  return this;
}

transpileString* transpileString::TranspileReplaceBetween(std::string *code) {
  if (!helper::String::Contains(*code, "#replaceBetween")) return this;

  std::regex exp2("#replaceBetween (.*) (.*) (.*) (.*)");
  std::string replacement = "$(" + path_binary_ + " replaceBetween $1 $2 $3 $4);";

  *code = std::regex_replace(*code, exp2, replacement);

  return this;
}

transpileString* transpileString::TranspileReplaceFirst(std::string *code) {
  if (!helper::String::Contains(*code, "#replaceFirst")) return this;

  std::regex exp2("#replaceFirst (.*) (.*) (.*)");
  std::string replacement = "$(" + path_binary_ + " replaceFirst $1 $2 $3);";

  *code = std::regex_replace(*code, exp2, replacement);

  return this;
}

transpileString* transpileString::TranspileReplaceLast(std::string *code) {
  if (!helper::String::Contains(*code, "#replaceLast")) return this;

  std::regex exp2("#replaceLast (.*) (.*) (.*)");
  std::string replacement = "$(" + path_binary_ + " replaceLast $1 $2 $3);";

  *code = std::regex_replace(*code, exp2, replacement);

  return this;
}

}  // namespace doShell
