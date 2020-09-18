// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#include <doShell/dosh/transpile/transpile_macro.h>

namespace doShell {

void transpileMacros::Transpile(std::string *code, bool is_linux) {
//  helper::String::ReplaceAll(code, "::HOUR::", "$(date +\"%k\")");
//  helper::String::ReplaceAll(code, "::DATE::", "$(date +\"%D\")");
//  helper::String::ReplaceAll(code, "::NOW::", "$(date)");
//  helper::String::ReplaceAll(code, "::TIME::", "$(date +\"%T\")");
  helper::String::ReplaceAll(code, "::TIMESTAMP::", "$(date +\"%s\")");
}

}  // namespace doShell
