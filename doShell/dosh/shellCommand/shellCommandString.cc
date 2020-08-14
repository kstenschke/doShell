// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#include <doShell/dosh/shellCommand/shellCommandString.h>

namespace doShell {

// Constructor: init (resolve) command and arguments
shellCommandString::shellCommandString(
    int argc, const std::vector<std::string> &argv) {
  argc_ = argc;
  argv_ = argv;

  // ...
}

shellCommandString::~shellCommandString() {
}

// Replace all occurrences of given string
bool shellCommandString::ReplaceAll() const {
  if (argc_ < 3) return false;

  std::string kHaystack = argv_[2];
  const std::string kNeedle = argv_[3];
  const std::string kReplacement = argc_ < 5 ? "" : argv_[4];

  helper::String::ReplaceAll(&kHaystack, kNeedle, kReplacement);

  std::cout << kHaystack;

  return true;
}

// Replace everything after and including the first occurrences of given string
bool shellCommandString::ReplaceAfter() const {
  if (argc_ < 3) return false;

  std::string kHaystack = argv_[2];
  const std::string kNeedle = argv_[3];
  const std::string kReplacement = argc_ < 5 ? "" : argv_[4];

  auto offset_needle = kHaystack.find(kNeedle);
  if (offset_needle == std::string::npos) offset_needle = kHaystack.length();

  std::cout << kHaystack.substr(0, offset_needle) + kReplacement;

  return true;
}

// Replace first occurrence of given string
bool shellCommandString::ReplaceFirst() const {
  if (argc_ < 3) return false;

  std::string kHaystack = argv_[2];
  const std::string kNeedle = argv_[3];
  const std::string kReplacement = argc_ < 5 ? "" : argv_[4];

  helper::String::ReplaceFirst(&kHaystack, kNeedle, kReplacement);

  std::cout << kHaystack;

  return true;
}

// Replace everything before and including the first occurrences of given string
bool shellCommandString::ReplaceBefore() const {
  if (argc_ < 3) return false;

  std::string kHaystack = argv_[2];
  const std::string kNeedle = argv_[3];
  const std::string kReplacement = argc_ < 5 ? "" : argv_[4];

  auto offset_needle = kHaystack.find(kNeedle);

  if (offset_needle == std::string::npos) {
    std::cout << kHaystack;

    return false;
  }

  kHaystack.replace(0, offset_needle + kNeedle.length(), kReplacement);

  std::cout << kHaystack;

  return true;
}

// Extract text excluding but between "before" and "after"
bool shellCommandString::ExtractBetween() const {
  if (argc_ < 3) return false;

  std::string kHaystack = argv_[2];
  const std::string kBefore = argv_[3];
  const std::string kAfter = argc_ < 5 ? "" : argv_[4];

  std::cout << helper::String::GetSubStrBetween(kHaystack, kBefore.c_str(), kAfter.c_str());

  return true;
}

}  // namespace doShell
