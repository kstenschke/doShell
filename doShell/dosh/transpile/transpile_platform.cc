// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#include <doShell/dosh/transpile/transpile_platform.h>
#include <iostream>

namespace doShell {

void transpilePlatform::Transpile(std::string *code) {
  transpilePlatformConditions(code);
  transpilePlatformConstants(code);
}

void transpilePlatform::transpilePlatformConditions(std::string *code) {
  if (!helper::String::Contains(*code, "#if_is_linux")
    &&!helper::String::Contains(*code, "#if_is_mac")) return;

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
}

void transpilePlatform::transpilePlatformConstants(std::string *code) {
  #if __linux__
    helper::String::ReplaceAll(code, "::OS::", "linux");
  #else
    helper::String::ReplaceAll(code, "::OS::", "mac");
  #endif
}

}  // namespace doShell
