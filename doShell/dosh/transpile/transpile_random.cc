// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#include <doShell/dosh/transpile/transpile_random.h>

namespace doShell {

void transpileRandom::Transpile(std::string *code) {
  if (!helper::String::Contains(*code, "#random ")) return;

  // Random one of given strings
  // TODO(kay) implement
//  std::string replacement = "$(( $RANDOM % ($2 - $1 + 1) + $1 ));";
//  std::regex exp("#random ('.*') ('.*')");
//
//  *code = std::regex_replace(*code, exp, replacement);

  // Random number in range of given min - max
  std::regex exp2("#random (\\d+) (\\d+)");
  std::string replacement = "$(( $RANDOM % ($2 - $1 + 1) + $1 ));";

  *code = std::regex_replace(*code, exp2, replacement);
}

}  // namespace doShell
