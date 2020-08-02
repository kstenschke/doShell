// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#include <doShell/dosh/shellCommand/shellCommandClipboard.h>

namespace doShell {

// Constructor: init (resolve) command and arguments
shellCommandClipboard::shellCommandClipboard(int argc, const std::vector<std::string> &argv) {
  argc_ = argc;
  argv_ = argv;

  // ...
}

shellCommandClipboard::~shellCommandClipboard() {
}

bool shellCommandClipboard::saveClipboardToFile(std::string path_file) {

  return true;
}


}  // namespace doShell
