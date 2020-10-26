// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#include <doShell/dosh/transpile/transpile_platform.h>
#include <iostream>

namespace doShell {

transpilePlatform::transpilePlatform(std::string *code) {
  code_ = code;
}

void transpilePlatform::Transpile(std::string *code) {
  auto *instance = new transpilePlatform(code);

  instance
    ->transpilePlatformConditions()
    ->transpilePlatformConstants();

  delete instance;
}

transpilePlatform* transpilePlatform::transpilePlatformConditions() {
  if (!helper::String::Contains(*code_, "#if_is_linux")
    &&!helper::String::Contains(*code_, "#if_is_mac")) return this;

  #if __linux__
    while (helper::String::Contains(*code_, "#if_is_mac")) {
      *code_ =
          helper::String::ReplaceBetween(*code_, "#if_is_mac", "#endif_is_mac");
    }
  #else
    while (helper::String::Contains(*code_, "#if_is_linux")) {
      *code_ = helper::String::ReplaceBetween(
          *code_, "#if_is_linux", "#endif_is_linux");
    }
  #endif

  helper::String::ReplaceAll(code_, "#if_is_linux");
  helper::String::ReplaceAll(code_, "#if_is_mac");
  helper::String::ReplaceAll(code_, "#endif_is_linux");
  helper::String::ReplaceAll(code_, "#endif_is_mac");

  return this;
}

transpilePlatform* transpilePlatform::transpilePlatformConstants() {
  #if __linux__
    helper::String::ReplaceAll(code_, "::OS::", "linux");
  #else
    helper::String::ReplaceAll(code_, "::OS::", "mac");
  #endif

  return this;
}

}  // namespace doShell
