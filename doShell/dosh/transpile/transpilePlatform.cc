// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#include <doShell/dosh/transpile/transpilePlatform.h>
#include <iostream>

namespace doShell {

bool transpilePlatform::Transpile(std::string *code, bool is_linux) {
  auto result = transpilePlatformConditions(code, is_linux);
  auto result2 = transpilePlatformConstants(code, is_linux);

  return result || result2;
}

bool transpilePlatform::transpilePlatformConditions(std::string *code,
                                                    bool is_linux) {
  if (!helper::String::Contains(*code, "#IF_IS_LINUX")
    &&!helper::String::Contains(*code, "#IF_IS_MAC")) return false;

  if (is_linux) {
    while (helper::String::Contains(*code, "#IF_IS_MAC")) {
      *code =
          helper::String::ReplaceBetween(*code, "#IF_IS_MAC", "#ENDIF_IS_MAC");
    }
  } else {
    while (helper::String::Contains(*code, "#IF_IS_LINUX")) {
      *code = helper::String::ReplaceBetween(
          *code, "#IF_IS_LINUX", "#ENDIF_IS_LINUX");
    }
  }

  helper::String::ReplaceAll(code, "#IF_IS_LINUX");
  helper::String::ReplaceAll(code, "#IF_IS_MAC");
  helper::String::ReplaceAll(code, "#ENDIF_IS_LINUX");
  helper::String::ReplaceAll(code, "#ENDIF_IS_MAC");

  return true;
}

bool transpilePlatform::transpilePlatformConstants(std::string *code,
                                                    bool is_linux) {
  return helper::String::ReplaceAll(
        code,
        "::OS::",
        is_linux ? "linux" : "mac") > 0;
}

}  // namespace doShell
