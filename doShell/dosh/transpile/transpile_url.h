// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#ifndef DOSHELL_DOSH_TRANSPILE_TRANSPILE_URL_H_
#define DOSHELL_DOSH_TRANSPILE_TRANSPILE_URL_H_

#include <doShell/helper/helper_string.h>
#include <string>

namespace doShell {
class transpileUrl {
 public:
  explicit transpileUrl(std::string *code, std::string path_binary);

  static void Transpile(std::string *code, std::string path_binary);

 private:
  std::string *code_;
  std::string path_binary_;

  transpileUrl* TranspileGetScheme();
  transpileUrl* TranspileGetQuery();
  transpileUrl* TranspileGetPath();
  transpileUrl* TranspileGetHost();
  transpileUrl* TranspileEncode();
  transpileUrl* TranspileDecode();
};
}  // namespace doShell

#endif  // DOSHELL_DOSH_TRANSPILE_TRANSPILE_URL_H_
