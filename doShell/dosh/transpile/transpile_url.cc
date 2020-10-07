// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#include <doShell/dosh/transpile/transpile_url.h>

#include <utility>

namespace doShell {

transpileUrl::transpileUrl(std::string *code, std::string path_binary) {
  code_ = code;
  path_binary_ = std::move(path_binary);
}

void transpileUrl::Transpile(std::string *code, std::string path_binary) {
  auto *instance = new transpileUrl(code, std::move(path_binary));

  if (helper::String::Contains(*code, "FromUrl ")) {
    instance
        ->TranspileGetScheme()
        ->TranspileGetQuery()
        ->TranspileGetPath()
        ->TranspileGetHost();
  }

  if (!helper::String::Contains(*code, "#url")) {
    delete instance;

    return;
  }

  instance
      ->TranspileEncode()
      ->TranspileDecode();

  delete instance;
}

transpileUrl* transpileUrl::TranspileDecode() {
  if (!helper::String::Contains(*code_, "#urlDecode")) return this;

  std::regex exp2("#urlDecode (.*)");
  std::string replacement = "$(" + path_binary_ + " urlDecode $1)";

  *code_ = std::regex_replace(*code_, exp2, replacement);

  return this;
}

transpileUrl* transpileUrl::TranspileEncode() {
  if (!helper::String::Contains(*code_, "#urlEncode")) return this;

  std::regex exp2("#urlEncode (.*)");
  std::string replacement = "$(" + path_binary_ + " urlEncode $1)";

  *code_ = std::regex_replace(*code_, exp2, replacement);

  return this;
}

transpileUrl* transpileUrl::TranspileGetHost() {
  if (!helper::String::Contains(*code_, "#getHostFromUrl")) return this;

  std::regex exp2("#getHostFromUrl (.*)");
  std::string replacement = "$(" + path_binary_ + " getHostFromUrl $1)";

  *code_ = std::regex_replace(*code_, exp2, replacement);

  return this;
}

transpileUrl* transpileUrl::TranspileGetPath() {
  if (!helper::String::Contains(*code_, "#getPathFromUrl")) return this;

  std::regex exp2("#getPathFromUrl (.*)");
  std::string replacement = "$(" + path_binary_ + " getPathFromUrl $1)";

  *code_ = std::regex_replace(*code_, exp2, replacement);

  return this;
}

transpileUrl* transpileUrl::TranspileGetQuery() {
  if (!helper::String::Contains(*code_, "#getQueryFromUrl")) return this;

  std::regex exp2("#getQueryFromUrl (.*)");
  std::string replacement = "$(" + path_binary_ + " getQueryFromUrl $1)";

  *code_ = std::regex_replace(*code_, exp2, replacement);

  return this;
}


transpileUrl* transpileUrl::TranspileGetScheme() {
  if (!helper::String::Contains(*code_, "#getSchemeFromUrl")) return this;

  std::regex exp2("#getSchemeFromUrl (.*)");
  std::string replacement = "$(" + path_binary_ + " getSchemeFromUrl $1)";

  *code_ = std::regex_replace(*code_, exp2, replacement);

  return this;
}

}  // namespace doShell
