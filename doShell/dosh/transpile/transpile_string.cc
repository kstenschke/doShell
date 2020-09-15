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

  TranspileReplaceAfter(code);
  TranspileReplaceAll(code);
  TranspileReplaceBefore(code);
  TranspileReplaceBetween(code);
  TranspileReplaceFirst(code);
  TranspileReplaceLast(code);

  delete instance;
}

bool transpileString::TranspileExtractBetween(std::string *code) {
  if (!helper::String::Contains(*code, "#extractBetween")) return false;

  std::regex exp2("#extractBetween (.*) (.*) (.*)");
  std::string replacement = "$(" + path_binary_ + " extractBetween $1 $2 $3);";

  *code = std::regex_replace(*code, exp2, replacement);

  return true;
}

bool transpileString::TranspileReplaceAfter(std::string *code) {
  return 0 < helper::String::ReplaceAll(
      code, "#replaceAfter", "dosh replaceAfter");
}

bool transpileString::TranspileReplaceAll(std::string *code) {
  return 0 < helper::String::ReplaceAll(
      code, "#replaceAll", "dosh replaceAll");
}

bool transpileString::TranspileReplaceBefore(std::string *code) {
  return 0 < helper::String::ReplaceAll(
      code, "#replaceBefore", "dosh replaceBefore");
}

bool transpileString::TranspileReplaceBetween(std::string *code) {
  return 0 < helper::String::ReplaceAll(
      code, "#replaceBefore", "dosh replaceBefore");
}

bool transpileString::TranspileReplaceFirst(std::string *code) {
  return 0 < helper::String::ReplaceAll(
      code, "#replaceFirst", "dosh replaceFirst");
}

bool transpileString::TranspileReplaceLast(std::string *code) {
  return 0 < helper::String::ReplaceAll(
      code, "#replaceLast", "dosh replaceLast");
}

}  // namespace doShell
