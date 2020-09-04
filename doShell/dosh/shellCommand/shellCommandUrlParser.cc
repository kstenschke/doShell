// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#include <doShell/dosh/shellCommand/shellCommandUrlParser.h>

namespace doShell {

// Constructor: init (resolve) command and arguments
shellCommandUrlParser::shellCommandUrlParser(
    int argc, const std::vector<std::string> &argv) {
  argc_ = argc;
  argv_ = argv;

  // ...
}

shellCommandUrlParser::~shellCommandUrlParser() {
}

// Extract scheme from given URL, e.g. http or https
bool shellCommandUrlParser::GetSchemeFromUrl() const {
  if (argc_ < 3) return false;

  std::string kUrl = argv_[2];

  unsigned long offsetColon = kUrl.find(':');

  if (offsetColon == std::string::npos) return false;

  std::cout << kUrl.substr(0, offsetColon);

  return true;
}

// Extract host from given URL, e.g. www.example.com
bool shellCommandUrlParser::GetHostFromUrl() const {
  if (argc_ < 3) return false;

  std::string kUrl = argv_[2];

  unsigned long offsetColon = kUrl.find(':');

  if (offsetColon == std::string::npos) return false;

  unsigned long offsetSlash = kUrl.find('/', offsetColon);

  if (offsetSlash == std::string::npos) offsetSlash = kUrl.length();

  std::cout << kUrl.substr(offsetColon + 1, offsetSlash - offsetColon);

  return true;
}

// Extract path from given URL, e.g. /foo/bar
bool shellCommandUrlParser::GetPathFromUrl() const {
}

// Extract query from given URL, e.g. hat=bowler&accessory=cane
bool shellCommandUrlParser::GetQueryFromUrl() const {
  if (argc_ < 3) return false;

  std::string kUrl = argv_[2];

  std::cout << helper::String::GetSubStrAfter(kUrl, "?");

  return true;
}

}  // namespace doShell
