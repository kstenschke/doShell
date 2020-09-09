// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#include <doShell/dosh/shell_command/shell_command_url_parse.h>

namespace doShell {

// Constructor: init (resolve) command and arguments
shellCommandUrlParse::shellCommandUrlParse(
    int argc, const std::vector<std::string> &argv) {
  argc_ = argc;
  argv_ = argv;

  // ...
}

shellCommandUrlParse::~shellCommandUrlParse() {
}

// Extract scheme from given URL, e.g. http or https
bool shellCommandUrlParse::GetSchemeFromUrl() const {
  if (argc_ < 3) return false;

  std::string kUrl = argv_[2];

  auto offsetColon = kUrl.find(':');

  if (offsetColon == std::string::npos) return false;

  std::cout << kUrl.substr(0, offsetColon);

  return true;
}

// Extract host from given URL, e.g. www.example.com
bool shellCommandUrlParse::GetHostFromUrl() const {
  if (argc_ < 3) return false;

  std::string kUrl = argv_[2];

  auto offsetColon = kUrl.find(':');

  if (offsetColon == std::string::npos) return false;

  auto offsetSlash = kUrl.find('/', offsetColon);

  if (offsetSlash == std::string::npos) offsetSlash = kUrl.length();

  std::cout << kUrl.substr(offsetColon + 1, offsetSlash - offsetColon);

  return true;
}

// Extract path from given URL, e.g. /foo/bar
bool shellCommandUrlParse::GetPathFromUrl() const {
}

// Extract query from given URL, e.g. hat=bowler&accessory=cane
bool shellCommandUrlParse::GetQueryFromUrl() const {
  if (argc_ < 3) return false;

  std::string kUrl = argv_[2];

  std::cout << helper::String::GetSubStrAfter(kUrl, "?");

  return true;
}

}  // namespace doShell
