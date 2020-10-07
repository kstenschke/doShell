// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#ifndef DOSHELL_DOSH_TRANSPILE_TRANSPILE_RANDOM_H_
#define DOSHELL_DOSH_TRANSPILE_TRANSPILE_RANDOM_H_

#include <doShell/helper/helper_string.h>
#include <string>

namespace doShell {
class transpileRandom {
 public:
  explicit transpileRandom(std::string *code);
  static void Transpile(std::string *code);

  transpileRandom* TranspileRandomNumber();

 private:
  std::string *code_;
};
}  // namespace doShell

#endif  // DOSHELL_DOSH_TRANSPILE_TRANSPILE_RANDOM_H_
