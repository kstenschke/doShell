// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#include <doShell/dosh/transpile/transpileRandom.h>

namespace doShell {

bool transpileRandom::Transpile(std::string *code, bool is_linux) {
  if (!helper::String::Contains(*code, "#random ")) return false;

  // Random number in range of given min - max
  std::string replacement = "$(( $RANDOM % ($2 - $1 + 1) + $1 ));";
  std::regex exp("#random (\\d+) (\\d+)");

  *code = std::regex_replace(*code, exp, replacement);

  return true;
}

}  // namespace doShell
