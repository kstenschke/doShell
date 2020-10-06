// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#include <doShell/dosh/transpile/transpile_platform.h>
#include <iostream>

namespace doShell {

bool transpilePlatform::Transpile(std::string *code) {
  auto result = transpilePlatformConditions(code);
  auto result2 = transpilePlatformConstants(code);

  return result || result2;
}

bool transpilePlatform::transpilePlatformConditions(std::string *code) {
  if (!helper::String::Contains(*code, "#if_is_linux")
    &&!helper::String::Contains(*code, "#if_is_mac")) return false;

  #if __linux__
    while (helper::String::Contains(*code, "#if_is_mac")) {
      *code =
          helper::String::ReplaceBetween(*code, "#if_is_mac", "#endif_is_mac");
    }
  #else
    while (helper::String::Contains(*code, "#if_is_linux")) {
      *code = helper::String::ReplaceBetween(
          *code, "#if_is_linux", "#endif_is_linux");
    }
  #endif

  helper::String::ReplaceAll(code, "#if_is_linux");
  helper::String::ReplaceAll(code, "#if_is_mac");
  helper::String::ReplaceAll(code, "#endif_is_linux");
  helper::String::ReplaceAll(code, "#endif_is_mac");

  return true;
}

bool transpilePlatform::transpilePlatformConstants(std::string *code) {
  #if __linux__
    return helper::String::ReplaceAll(code, "::OS::", "linux") > 0;
  #else
    return helper::String::ReplaceAll(code, "::OS::", "mac") > 0;
  #endif
}

}  // namespace doShell
