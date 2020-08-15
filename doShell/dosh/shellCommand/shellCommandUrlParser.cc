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

}

// Extract host from given URL, e.g. www.example.com
bool shellCommandUrlParser::GetHostFromUrl() const {

}

// Extract path from given URL, e.g. /foo/bar
bool shellCommandUrlParser::GetPathFromUrl() const {

}

// Extract query from given URL, e.g. hat=bowler&accessory=cane
bool shellCommandUrlParser::GetQueryFromUrl() const {

}

}  // namespace doShell
