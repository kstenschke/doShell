// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#include <doShell/dosh/shell_command/shell_command_clipboard.h>
#include <vendor/clip/clip.h>

namespace doShell {

// TODO(kay): implement/test loadIntoClipboard
// TODO(kay): implement/test prependClipboard

// Constructor: init (resolve) command and arguments
shellCommandClipboard::shellCommandClipboard(
    int argc, const std::vector<std::string> &argv) {
  argc_ = argc;
  argv_ = argv;

  // ...
}

shellCommandClipboard::~shellCommandClipboard() {
}

// Extract text excluding but between "before" and "after"
bool shellCommandClipboard::ExtractBetween() const {
  if (argc_ < 3) return false;

  std::string kHaystack;
  clip::get_text(kHaystack);

  int arg_offset_before = 2, arg_offset_after = 3;

  const std::string kBefore = argv_[arg_offset_before];

  const std::string kAfter = argc_ <= arg_offset_after
                             ? ""
                             : argv_[arg_offset_after];

  kHaystack = helper::String::GetSubStrBetween(
      kHaystack, kBefore.c_str(), kAfter.c_str());

  std::cout << kHaystack;

  clip::set_text(kHaystack);

  return true;
}

bool shellCommandClipboard::SaveClipboardToFile(std::string path_file) {
  std::string value;
  clip::get_text(value);

  return helper::File::WriteToNewFile(path_file, value);
}

bool shellCommandClipboard::SetClipboard(std::string str) {
  return clip::set_text(str);
}

bool shellCommandClipboard::AppendClipboardToFile(std::string path_file) {
  std::string value;
  clip::get_text(value);

  return helper::File::AppendToFile(path_file, value) > 0;
}

bool shellCommandClipboard::PasteRenderedFromFile(
    const std::string &templateFile, const std::string &json_replacements) {

  if (!helper::File::FileExists(templateFile)) {
    std::cerr << "File not found: " + templateFile + "\n";

    return false;
  }

//  if (!helper::String::IsJson(json_replacements)) {
//    std::cerr << "Not valid JSON: " + json_replacements + "\n";
//
//    return false;
//  }

  std::string tmpl;
  helper::File::GetFileContents(templateFile, &tmpl);

  // TODO(kay): replace from json tuples

  clip::set_text(tmpl);

  return true;
}

bool shellCommandClipboard::PregMatchAll(std::string pattern) {
  std::string str;
  clip::get_text(str);

  if (str.empty()) return false;

  std::regex r(pattern);
  std::smatch sm;

  while (regex_search(str, sm, r)) {
    std::cout << sm.str() << '\n';
    str = sm.suffix();
  }

  return true;
}

// Replace all occurrences of given string
bool shellCommandClipboard::ReplaceAll() const {
  if (argc_ < 3) return false;

  std::string kHaystack;
  clip::get_text(kHaystack);

  int arg_offset_needle = 2, arg_offset_replacement = 3;

  const std::string kNeedle = argv_[arg_offset_needle];

  const std::string kReplacement = argc_ <= arg_offset_replacement
                                   ? ""
                                   : argv_[arg_offset_replacement];

  helper::String::ReplaceAll(&kHaystack, kNeedle, kReplacement);

  std::cout << kHaystack;

  clip::set_text(kHaystack);

  return true;
}

// Replace everything after and including the first occurrences of given string
bool shellCommandClipboard::ReplaceAfter() const {
  if (argc_ < 3) return false;

  std::string kHaystack;
  clip::get_text(kHaystack);

  int arg_offset_needle = 2, arg_offset_replacement = 3;

  const std::string kNeedle = argv_[arg_offset_needle];

  const std::string kReplacement = argc_ <= arg_offset_replacement
                                   ? ""
                                   : argv_[arg_offset_replacement];

  auto offset_needle = kHaystack.find(kNeedle);
  if (offset_needle == std::string::npos) offset_needle = kHaystack.length();

  kHaystack = kHaystack.substr(0, offset_needle) + kReplacement;

  std::cout << kHaystack;

  clip::set_text(kHaystack);

  return true;
}

// Replace everything before and including the first occurrences of given string
bool shellCommandClipboard::ReplaceBefore() const {
  if (argc_ < 3) return false;

  std::string kHaystack;
  clip::get_text(kHaystack);

  int arg_offset_needle = 2, arg_offset_replacement = 3;

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

  clip::set_text(kHaystack);

  return true;
}

// Replace text including and between "before" and "after"
bool shellCommandClipboard::ReplaceBetween() const {
  if (argc_ < 3) return false;

  std::string kHaystack;
  clip::get_text(kHaystack);

  int arg_offset_before = 2, arg_offset_after = 3, arg_offset_replacement = 4;

  const std::string kBefore = argv_[arg_offset_before];
  const std::string kAfter = argv_[arg_offset_after];

  const std::string kReplacement = argc_ <= arg_offset_replacement
                                   ? ""
                                   : argv_[arg_offset_replacement];

  kHaystack =
      helper::String::ReplaceBetween(kHaystack, kBefore, kAfter, kReplacement);

  if (kHaystack.empty()) return false;

  std::cout << kHaystack;

  clip::set_text(kHaystack);

  return true;
}

// Replace first occurrence of given string
bool shellCommandClipboard::ReplaceFirst() const {
  if (argc_ < 3) return false;

  std::string kHaystack;
  clip::get_text(kHaystack);

  int arg_offset_needle = 3, arg_offset_replacement = 4;

  const std::string kNeedle = argv_[arg_offset_needle];

  const std::string kReplacement = argc_ <= arg_offset_replacement
                                   ? ""
                                   : argv_[arg_offset_replacement];

  helper::String::ReplaceFirst(&kHaystack, kNeedle, kReplacement);

  std::cout << kHaystack;

  clip::set_text(kHaystack);

  return true;
}

// Replace last occurrence of given string
bool shellCommandClipboard::ReplaceLast() const {
  if (argc_ < 3) return false;

  std::string kHaystack;
  clip::get_text(kHaystack);

  int arg_offset_needle = 2, arg_offset_replacement = 3;

  const std::string kNeedle = argv_[arg_offset_needle];

  const std::string kReplacement = argc_ <= arg_offset_replacement
                                   ? ""
                                   : argv_[arg_offset_replacement];

  helper::String::ReplaceLast(&kHaystack, kNeedle, kReplacement);

  std::cout << kHaystack;

  clip::set_text(kHaystack);

  return true;
}

}  // namespace doShell
