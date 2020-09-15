// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#ifndef DOSHELL_DOSH_TRANSPILE_TRANSPILE_STRING_H_
#define DOSHELL_DOSH_TRANSPILE_TRANSPILE_STRING_H_

#include <doShell/helper/helper_string.h>
#include <string>

namespace doShell {
class transpileString {
 public:

  transpileString(std::string path_binary);

  static void Transpile(
      std::string *code, bool is_linux, std::string path_binary);

 private:
  std::string path_binary_;

  bool TranspileExtractBetween(std::string *code);
  bool TranspileReplaceAfter(std::string *code);
  bool TranspileReplaceAll(std::string *code);
  bool TranspileReplaceBefore(std::string *code);
  bool TranspileReplaceBetween(std::string *code);
  bool TranspileReplaceFirst(std::string *code);
  bool TranspileReplaceLast(std::string *code);
};
}  // namespace doShell

#endif  // DOSHELL_DOSH_TRANSPILE_TRANSPILE_STRING_H_
