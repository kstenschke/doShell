// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#ifndef DOSHELL_DOSH_TRANSPILE_TRANSPILE_STRING_H_
#define DOSHELL_DOSH_TRANSPILE_TRANSPILE_STRING_H_

#include <doShell/helper/helper_string.h>
#include <string>

namespace doShell {
class transpileString {
 public:
  static void Transpile(std::string *code, bool is_linux);

 private:
  static bool TranspileExtractBetween(std::string *code);
  static bool TranspileReplaceAfter(std::string *code);
  static bool TranspileReplaceAll(std::string *code);
  static bool TranspileReplaceBefore(std::string *code);
  static bool TranspileReplaceBetween(std::string *code);
  static bool TranspileReplaceFirst(std::string *code);
  static bool TranspileReplaceLast(std::string *code);
};
}  // namespace doShell

#endif  // DOSHELL_DOSH_TRANSPILE_TRANSPILE_STRING_H_
