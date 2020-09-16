// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#include <doShell/dosh/transpile/transpile_macro.h>

namespace doShell {

void transpileMacros::Transpile(std::string *code, bool is_linux) {
  helper::String::ReplaceAll(code, "::DATE::", "$(date +\"%D\")");
  helper::String::ReplaceAll(code, "::DATE_TIME::", "$(date)");
  helper::String::ReplaceAll(code, "::TIME::", "$(date +\"%T\")");
}

}  // namespace doShell
