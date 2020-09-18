// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#ifndef DOSHELL_DOSH_TRANSPILE_TRANSPILE_URL_H_
#define DOSHELL_DOSH_TRANSPILE_TRANSPILE_URL_H_

#include <doShell/helper/helper_string.h>
#include <string>

namespace doShell {
class transpileUrl {
 public:
  transpileUrl(std::string path_binary);

  static void Transpile(
      std::string *code, bool is_linux, std::string path_binary);

 private:
  std::string path_binary_;

  transpileUrl* TranspileGetScheme(std::string *code);
  transpileUrl* TranspileGetQuery(std::string *code);
  transpileUrl* TranspileGetPath(std::string *code);
  transpileUrl* TranspileGetHost(std::string *code);
  transpileUrl* TranspileEncode(std::string *code);
  transpileUrl* TranspileDecode(std::string *code);
};
}  // namespace doShell

#endif  // DOSHELL_DOSH_TRANSPILE_TRANSPILE_URL_H_
