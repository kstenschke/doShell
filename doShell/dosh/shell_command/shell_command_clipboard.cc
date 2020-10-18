// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#include <doShell/dosh/shell_command/shell_command_clipboard.h>
#include <vendor/clip/clip.h>

namespace doShell {

// Constructor: init (resolve) command and arguments
shellCommandClipboard::shellCommandClipboard(
    int argc, const std::vector<std::string> &argv) {
  argc_ = argc;
  argv_ = argv;

  // ...
}

shellCommandClipboard::~shellCommandClipboard() {
}

bool shellCommandClipboard::saveClipboardToFile(std::string path_file) {
  std::string value;
  clip::get_text(value);

  return helper::File::WriteToNewFile(path_file, value);
}

bool shellCommandClipboard::setClipboard(std::string str) {
  return clip::set_text(str);
}

bool shellCommandClipboard::appendClipboardToFile(std::string path_file) {
  std::string value;
  clip::get_text(value);

  return helper::File::AppendToFile(path_file, value) > 0;
}

bool shellCommandClipboard::pregMatchAll(std::string pattern) {
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

}  // namespace doShell
