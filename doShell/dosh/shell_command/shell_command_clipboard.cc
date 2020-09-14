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

bool shellCommandClipboard::appendClipboardToFile(std::string path_file) {
  std::string value;
  clip::get_text(value);

  return helper::File::AppendToFile(path_file, value);
}

}  // namespace doShell
