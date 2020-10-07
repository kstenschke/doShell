// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#ifndef DOSHELL_DOSH_TRANSPILE_TRANSPILE_PLATFORM_H_
#define DOSHELL_DOSH_TRANSPILE_TRANSPILE_PLATFORM_H_

#include <doShell/helper/helper_string.h>
#include <string>

namespace doShell {
class transpilePlatform {
 public:
  static void Transpile(std::string *code);

 private:
  static void transpilePlatformConditions(std::string *code);
  static void transpilePlatformConstants(std::string *code);
};
}  // namespace doShell

#endif  // DOSHELL_DOSH_TRANSPILE_TRANSPILE_PLATFORM_H_
