// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#include <doShell/dosh/transpile/transpile_url.h>

namespace doShell {

bool transpileUrl::Transpile(std::string *code, bool is_linux) {
  auto res1 = helper::String::ReplaceAll(
      code, "#getSchemeFromUrl", "/home/kay/CLionProjects/shellDo/bin/linux/dosh getSchemeFromUrl");

  auto res2 = helper::String::ReplaceAll(
      code, "#getQueryFromUrl", "dosh getQueryFromUrl");

  auto res3 = helper::String::ReplaceAll(
      code, "#getPathFromUrl", "dosh getPathFromUrl");

  auto res4 = helper::String::ReplaceAll(
      code, "#getHostFromUrl", "dosh getHostFromUrl");

  return res1 || res2 || res3 || res4;
}

}  // namespace doShell
