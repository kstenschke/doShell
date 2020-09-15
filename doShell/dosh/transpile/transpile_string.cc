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

  instance->TranspileReplaceAfter(code);
  instance->TranspileReplaceAll(code);
  instance->TranspileReplaceBefore(code);
  instance->TranspileReplaceBetween(code);
  instance->TranspileReplaceFirst(code);
  instance->TranspileReplaceLast(code);

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
  if (!helper::String::Contains(*code, "#replaceAfter")) return false;

  std::regex exp2("#replaceAfter (.*) (.*) (.*)");
  std::string replacement = "$(" + path_binary_ + " replaceAfter $1 $2 $3);";

  *code = std::regex_replace(*code, exp2, replacement);

  return true;
}

bool transpileString::TranspileReplaceAll(std::string *code) {
  if (!helper::String::Contains(*code, "#replaceAll")) return false;

  std::regex exp2("#replaceAll (.*) (.*) (.*)");
  std::string replacement = "$(" + path_binary_ + " replaceAll $1 $2 $3);";

  *code = std::regex_replace(*code, exp2, replacement);

  return true;
}

bool transpileString::TranspileReplaceBefore(std::string *code) {
  if (!helper::String::Contains(*code, "#replaceBefore")) return false;

  std::regex exp2("#replaceBefore (.*) (.*) (.*)");
  std::string replacement = "$(" + path_binary_ + " replaceBefore $1 $2 $3);";

  *code = std::regex_replace(*code, exp2, replacement);

  return true;
}

bool transpileString::TranspileReplaceBetween(std::string *code) {
  if (!helper::String::Contains(*code, "#replaceBetween")) return false;

  std::regex exp2("#replaceBetween (.*) (.*) (.*) (.*)");
  std::string replacement = "$(" + path_binary_ + " replaceBetween $1 $2 $3 $4);";

  *code = std::regex_replace(*code, exp2, replacement);

  return true;
}

bool transpileString::TranspileReplaceFirst(std::string *code) {
  if (!helper::String::Contains(*code, "#replaceFirst")) return false;

  std::regex exp2("#replaceFirst (.*) (.*) (.*)");
  std::string replacement = "$(" + path_binary_ + " replaceFirst $1 $2 $3);";

  *code = std::regex_replace(*code, exp2, replacement);

  return true;
}

bool transpileString::TranspileReplaceLast(std::string *code) {
  if (!helper::String::Contains(*code, "#replaceLast")) return false;

  std::regex exp2("#replaceLast (.*) (.*) (.*)");
  std::string replacement = "$(" + path_binary_ + " replaceLast $1 $2 $3);";

  *code = std::regex_replace(*code, exp2, replacement);

  return true;
}

}  // namespace doShell
