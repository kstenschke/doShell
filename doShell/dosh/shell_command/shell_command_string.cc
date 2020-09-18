// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#include <doShell/dosh/shell_command/shell_command_string.h>

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
bool shellCommandString::ReplaceAll(std::string str) const {
  int amount_args_required = str.empty() ? 3 : 2;

  if (argc_ < amount_args_required) return false;

  std::string kHaystack;
  int arg_offset_needle, arg_offset_replacement;

  if (str.empty()) {
    // Haystack is given as CLI argument
    kHaystack = argv_[2];
    arg_offset_needle = 3;
    arg_offset_replacement = 4;
  } else {
    // Haystack is given as function parameter
    kHaystack = str;
    arg_offset_needle = 2;
    arg_offset_replacement = 3;
  }

  const std::string kNeedle = argv_[arg_offset_needle];

  const std::string kReplacement = argc_ <= arg_offset_replacement
                                   ? ""
                                   : argv_[arg_offset_replacement];

  helper::String::ReplaceAll(&kHaystack, kNeedle, kReplacement);

  std::cout << kHaystack;

  return true;
}

// Replace everything after and including the first occurrences of given string
bool shellCommandString::ReplaceAfter(std::string str) const {
  int amount_args_required = str.empty() ? 3 : 2;

  if (argc_ < amount_args_required) return false;

  std::string kHaystack;
  int arg_offset_needle, arg_offset_replacement;

  if (str.empty()) {
    // Haystack is given as CLI argument
    kHaystack = argv_[2];
    arg_offset_needle = 3;
    arg_offset_replacement = 4;
  } else {
    // Haystack is given as function parameter
    kHaystack = str;
    arg_offset_needle = 2;
    arg_offset_replacement = 3;
  }

  const std::string kNeedle = argv_[arg_offset_needle];

  const std::string kReplacement = argc_ <= arg_offset_replacement
                                   ? ""
                                   : argv_[arg_offset_replacement];

  auto offset_needle = kHaystack.find(kNeedle);
  if (offset_needle == std::string::npos) offset_needle = kHaystack.length();

  std::cout << kHaystack.substr(0, offset_needle) + kReplacement;

  return true;
}

// Replace first occurrence of given string
bool shellCommandString::ReplaceFirst(std::string str) const {
  int amount_args_required = str.empty() ? 3 : 2;

  if (argc_ < amount_args_required) return false;

  std::string kHaystack;
  int arg_offset_needle, arg_offset_replacement;

  if (str.empty()) {
    // Haystack is given as CLI argument
    kHaystack = argv_[2];
    arg_offset_needle = 3;
    arg_offset_replacement = 4;
  } else {
    // Haystack is given as function parameter
    kHaystack = str;
    arg_offset_needle = 2;
    arg_offset_replacement = 3;
  }

  const std::string kNeedle = argv_[arg_offset_needle];

  const std::string kReplacement = argc_ <= arg_offset_replacement
                                   ? ""
                                   : argv_[arg_offset_replacement];

  helper::String::ReplaceFirst(&kHaystack, kNeedle, kReplacement);

  std::cout << kHaystack;

  return true;
}

// Replace last occurrence of given string
bool shellCommandString::ReplaceLast(std::string str) const {
  int amount_args_required = str.empty() ? 3 : 2;

  if (argc_ < amount_args_required) return false;

  std::string kHaystack;
  int arg_offset_needle, arg_offset_replacement;

  if (str.empty()) {
    // Haystack is given as CLI argument
    kHaystack = argv_[2];
    arg_offset_needle = 3;
    arg_offset_replacement = 4;
  } else {
    // Haystack is given as function parameter
    kHaystack = str;
    arg_offset_needle = 2;
    arg_offset_replacement = 3;
  }

  const std::string kNeedle = argv_[arg_offset_needle];

  const std::string kReplacement = argc_ <= arg_offset_replacement
                                   ? ""
                                   : argv_[arg_offset_replacement];

  helper::String::ReplaceLast(&kHaystack, kNeedle, kReplacement);

  std::cout << kHaystack;

  return true;
}

// Replace everything before and including the first occurrences of given string
bool shellCommandString::ReplaceBefore(std::string str) const {
  int amount_args_required = str.empty() ? 3 : 2;

  if (argc_ < amount_args_required) return false;

  std::string kHaystack;
  int arg_offset_needle, arg_offset_replacement;

  if (str.empty()) {
    // Haystack is given as CLI argument
    kHaystack = argv_[2];
    arg_offset_needle = 3;
    arg_offset_replacement = 4;
  } else {
    // Haystack is given as function parameter
    kHaystack = str;
    arg_offset_needle = 2;
    arg_offset_replacement = 3;
  }

  const std::string kNeedle = argv_[arg_offset_needle];

  const std::string kReplacement = argc_ <= arg_offset_replacement
                                   ? ""
                                   : argv_[arg_offset_replacement];

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
bool shellCommandString::ExtractBetween(std::string str) const {
  int amount_args_required = str.empty() ? 3 : 2;

  if (argc_ < amount_args_required) return false;

  std::string kHaystack;
  int arg_offset_before, arg_offset_after;

  if (str.empty()) {
    // Haystack is given as CLI argument
    kHaystack = argv_[2];
    arg_offset_before = 3;
    arg_offset_after = 4;
  } else {
    // Haystack is given as function parameter
    kHaystack = str;
    arg_offset_before = 2;
    arg_offset_after = 3;
  }

  const std::string kBefore = argv_[arg_offset_before];

  const std::string kAfter = argc_ <= arg_offset_after
                             ? ""
                             : argv_[arg_offset_after];

  std::cout << helper::String::GetSubStrBetween(
      kHaystack, kBefore.c_str(), kAfter.c_str());

  return true;
}

// Replace text including and between "before" and "after"
bool shellCommandString::ReplaceBetween(std::string str) const {
  int amount_args_required = str.empty() ? 4 : 3;

  if (argc_ < amount_args_required) return false;

  std::string kHaystack;
  int arg_offset_before, arg_offset_after, arg_offset_replacement;

  if (str.empty()) {
    // Haystack is given as CLI argument
    kHaystack = argv_[2];
    arg_offset_before = 3;
    arg_offset_after = 4;
    arg_offset_replacement = 5;
  } else {
    // Haystack is given as function parameter
    kHaystack = str;
    arg_offset_before = 2;
    arg_offset_after = 3;
    arg_offset_replacement = 4;
  }

  const std::string kBefore = argv_[arg_offset_before];
  const std::string kAfter = argv_[arg_offset_after];

  const std::string kReplacement = argc_ <= arg_offset_replacement
                                   ? ""
                                   : argv_[arg_offset_replacement];

  auto out = helper::String::ReplaceBetween(
      kHaystack, kBefore, kAfter, kReplacement);

  if (out.empty()) return false;

  std::cout << out;

  return true;
}

}  // namespace doShell
