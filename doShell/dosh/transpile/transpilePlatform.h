// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#ifndef DOSHELL_DOSH_TRANSPILE_TRANSPILEPLATFORM_H_
#define DOSHELL_DOSH_TRANSPILE_TRANSPILEPLATFORM_H_

#include <doShell/helper/helper_string.h>
#include <string>

namespace doShell {
class transpilePlatform {
 public:
  static bool Transpile(std::string *code, bool is_linux);

 private:
  static bool transpilePlatformConditions(std::string *code, bool is_linux);
  static bool transpilePlatformConstants(std::string *code, bool is_linux);
};
}  // namespace doShell

#endif  // DOSHELL_DOSH_TRANSPILE_TRANSPILEPLATFORM_H_
