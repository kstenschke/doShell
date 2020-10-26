// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#ifndef DOSHELL_DOSH_TRANSPILE_TRANSPILE_STRING_H_
#define DOSHELL_DOSH_TRANSPILE_TRANSPILE_STRING_H_

#include <doShell/helper/helper_string.h>
#include <string>

namespace doShell {
class transpileString {
 public:
  transpileString(
      std::string *code,
      std::string path_binary,
      std::string from = "");

  static void Transpile(std::string *code,
                        const std::string &path_binary,
                        const std::string &from = "");

 private:
  std::string *code_;
  std::string path_binary_;
  std::string from_ = "";

  transpileString* TranspileExtractBetween();
  transpileString* TranspileReplaceAfter();
  transpileString* TranspileReplaceAll();
  transpileString* TranspileReplaceBefore();
  transpileString* TranspileReplaceBetween();
  transpileString* TranspileReplaceFirst();
  transpileString* TranspileReplaceLast();
};
}  // namespace doShell

#endif  // DOSHELL_DOSH_TRANSPILE_TRANSPILE_STRING_H_
