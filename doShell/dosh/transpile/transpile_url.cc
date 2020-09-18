// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#include <doShell/dosh/transpile/transpile_url.h>

#include <utility>

namespace doShell {

transpileUrl::transpileUrl(std::string path_binary) {
  path_binary_ = std::move(path_binary);
}

void transpileUrl::Transpile(
    std::string *code, bool is_linux, std::string path_binary) {
  auto *instance = new transpileUrl(std::move(path_binary));

  if (helper::String::Contains(*code, "FromUrl ")) {
    instance
        ->TranspileGetScheme(code)
        ->TranspileGetQuery(code)
        ->TranspileGetPath(code)
        ->TranspileGetHost(code);
  }

  if (!helper::String::Contains(*code, "#url")) {
    delete instance;

    return;
  }

  instance
      ->TranspileEncode(code)
      ->TranspileDecode(code);

  delete instance;
}

transpileUrl* transpileUrl::TranspileDecode(std::string *code) {
  if (!helper::String::Contains(*code, "#urlDecode")) return this;

  std::regex exp2("#urlDecode (.*)");
  std::string replacement = "$(" + path_binary_ + " urlDecode $1);";

  *code = std::regex_replace(*code, exp2, replacement);

  return this;
}

transpileUrl* transpileUrl::TranspileEncode(std::string *code) {
  if (!helper::String::Contains(*code, "#urlEncode")) return this;

  std::regex exp2("#urlEncode (.*)");
  std::string replacement = "$(" + path_binary_ + " urlEncode $1);";

  *code = std::regex_replace(*code, exp2, replacement);

  return this;
}

transpileUrl* transpileUrl::TranspileGetHost(std::string *code) {
  if (!helper::String::Contains(*code, "#getHostFromUrl")) return this;

  std::regex exp2("#getHostFromUrl (.*)");
  std::string replacement = "$(" + path_binary_ + " getHostFromUrl $1);";

  *code = std::regex_replace(*code, exp2, replacement);

  return this;
}

transpileUrl* transpileUrl::TranspileGetPath(std::string *code) {
  if (!helper::String::Contains(*code, "#getPathFromUrl")) return this;

  std::regex exp2("#getPathFromUrl (.*)");
  std::string replacement = "$(" + path_binary_ + " getPathFromUrl $1);";

  *code = std::regex_replace(*code, exp2, replacement);

  return this;
}

transpileUrl* transpileUrl::TranspileGetQuery(std::string *code) {
  if (!helper::String::Contains(*code, "#getQueryFromUrl")) return this;

  std::regex exp2("#getQueryFromUrl (.*)");
  std::string replacement = "$(" + path_binary_ + " getQueryFromUrl $1);";

  *code = std::regex_replace(*code, exp2, replacement);

  return this;
}


transpileUrl* transpileUrl::TranspileGetScheme(std::string *code) {
  if (!helper::String::Contains(*code, "#getSchemeFromUrl")) return this;

  std::regex exp2("#getSchemeFromUrl (.*)");
  std::string replacement = "$" + path_binary_ + " getSchemeFromUrl $1);";

  *code = std::regex_replace(*code, exp2, replacement);

  return this;
}

}  // namespace doShell
