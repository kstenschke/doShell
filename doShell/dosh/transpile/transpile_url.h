// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#ifndef DOSHELL_DOSH_TRANSPILE_TRANSPILE_URL_H_
#define DOSHELL_DOSH_TRANSPILE_TRANSPILE_URL_H_

#include <doShell/helper/helper_string.h>
#include <string>

namespace doShell {
class transpileUrl {
 public:
  static bool Transpile(std::string *code, bool is_linux);
};
}  // namespace doShell

#endif  // DOSHELL_DOSH_TRANSPILE_TRANSPILE_URL_H_
