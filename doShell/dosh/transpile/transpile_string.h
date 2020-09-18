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

  transpileString* TranspileExtractBetween(std::string *code);
  transpileString* TranspileReplaceAfter(std::string *code);
  transpileString* TranspileReplaceAll(std::string *code);
  transpileString* TranspileReplaceBefore(std::string *code);
  transpileString* TranspileReplaceBetween(std::string *code);
  transpileString* TranspileReplaceFirst(std::string *code);
  transpileString* TranspileReplaceLast(std::string *code);
};
}  // namespace doShell

#endif  // DOSHELL_DOSH_TRANSPILE_TRANSPILE_STRING_H_
