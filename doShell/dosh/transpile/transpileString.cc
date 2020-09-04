// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#include <doShell/dosh/transpile/transpileString.h>

namespace doShell {

void transpileString::Transpile(std::string *code, bool is_linux) {
  TranspileExtractBetween(code);

  if (!helper::String::Contains(*code, "#replace")) return;

  TranspileReplaceAfter(code);
  TranspileReplaceAll(code);
  TranspileReplaceBefore(code);
  TranspileReplaceBetween(code);
  TranspileReplaceFirst(code);
  TranspileReplaceLast(code);
}

bool transpileString::TranspileExtractBetween(std::string *code) {
  return 0 < helper::String::ReplaceAll(
      code, "#extractBetween", "dosh extractBetween");
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
