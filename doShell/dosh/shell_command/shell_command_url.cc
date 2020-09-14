// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#include <doShell/dosh/shell_command/shell_command_url.h>

namespace doShell {

// Constructor: init (resolve) command and arguments
shellCommandUrl::shellCommandUrl(
    int argc, const std::vector<std::string> &argv) {
  argc_ = argc;
  argv_ = argv;

  // ...
}

shellCommandUrl::~shellCommandUrl() {
}

// Extract scheme from given URL, e.g. http or https
bool shellCommandUrl::GetSchemeFromUrl() const {
  if (argc_ < 3) return false;

  std::string kUrl = argv_[2];

  auto offsetColon = kUrl.find(':');

  if (offsetColon == std::string::npos) return false;

  std::cout << kUrl.substr(0, offsetColon);

  return true;
}

// Extract host from given URL, e.g. www.example.com
bool shellCommandUrl::GetHostFromUrl() const {
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
bool shellCommandUrl::GetPathFromUrl() const {
  // TODO(kay) implement
  return true;
}

// Extract query from given URL, e.g. hat=bowler&accessory=cane
bool shellCommandUrl::GetQueryFromUrl() const {
  if (argc_ < 3) return false;

  std::string kUrl = argv_[2];

  std::cout << helper::String::GetSubStrAfter(kUrl, "?");

  return true;
}

bool shellCommandUrl::Encode() {
  if (argc_ < 3) return false;

  const std::string s = argv_[2];

  std::string encoded;

  for (char c : s) {
    if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
      encoded += c;
    } else {
      char hex[4];
      snprintf(hex, sizeof(hex), "%%%02x", c);
      encoded += hex;
    }
  }

  std::cout << encoded;

  return true;
}

bool shellCommandUrl::Decode() {
  if (argc_ < 3) return false;

  const std::string s = argv_[2];

  std::string decoded;

  for (auto i = 0; i < s.length(); i++) {
    if (s[i] == '%') {
      auto n = std::stoul(s.substr(i + 1, 2), nullptr, 16);
      decoded += static_cast<char>(n);
      i += 2;
    } else if (s[i] == '+') {
      decoded += ' ';
    } else {
      decoded += s[i];
    }
  }

  std::cout << decoded;

  return true;
}

}  // namespace doShell