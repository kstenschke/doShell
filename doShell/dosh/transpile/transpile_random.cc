// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#include <doShell/dosh/transpile/transpile_random.h>

namespace doShell {

transpileRandom::transpileRandom(std::string *code) {
  code_ = code;
}

void transpileRandom::Transpile(std::string *code) {
  if (!helper::String::Contains(*code, "_random ")) return;

  auto *instance = new transpileRandom(code);

  instance->TranspileRandomNumber();

  delete instance;
}

transpileRandom* transpileRandom::TranspileRandomNumber() {
  // Random one of given strings
  // TODO(kay) implement
//  std::string replacement = "$(( $RANDOM % ($2 - $1 + 1) + $1 ));";
//  std::regex exp("_random ('.*') ('.*')");
//
//  *code = std::regex_replace(*code, exp, replacement);

  // Random number in range of given min - max
  std::regex exp2("_random (\\d+) (\\d+)");
  std::string replacement = "$(( $RANDOM % ($2 - $1 + 1) + $1 ));";

  *code_ = std::regex_replace(*code_, exp2, replacement);

  return this;
}

}  // namespace doShell
