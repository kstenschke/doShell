// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#ifndef DOSHELL_SHELLCOMMANDCLIPBOARD_H
#define DOSHELL_SHELLCOMMANDCLIPBOARD_H

#include <doShell/app/app_argument.h>
#include <doShell/app/app_command.h>
#include <doShell/app/app_help.h>
#include <doShell/config.h>
#include <doShell/dosh/transpiler/transpileClipboard.h>
#include <doShell/dosh/transpiler/transpileBrowser.h>
#include <doShell/dosh/transpiler/transpileKeystrokes.h>
#include <doShell/helper/helper_cli.h>

#include <cstring>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

namespace doShell {

class shellCommandClipboard {
 public:
  // Constructor: init (resolve) command and arguments
  shellCommandClipboard(int argc, const std::vector<std::string>& argv);

  virtual ~shellCommandClipboard();

  static bool saveClipboardToFile(std::string path_file);

 private:
  int argc_;
  std::vector<std::string> argv_;
};

}  // namespace doShell

#endif  // DOSHELL_SHELLCOMMANDCLIPBOARD_H
