// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#ifndef DOSHELL_DOSH_SHELL_COMMAND_SHELL_COMMAND_CLIPBOARD_H_
#define DOSHELL_DOSH_SHELL_COMMAND_SHELL_COMMAND_CLIPBOARD_H_

#include <doShell/app/app_argument.h>
#include <doShell/app/app_command.h>
#include <doShell/app/app_help.h>
#include <doShell/config.h>
#include <doShell/dosh/transpile/transpile_clipboard.h>
#include <doShell/dosh/transpile/transpile_browser.h>
#include <doShell/dosh/transpile/transpile_keystrokes.h>
#include <doShell/helper/helper_cli.h>

#include <cstring>
#include <iostream>
#include <string>
#include <thread>  // NOLINT
#include <vector>

namespace doShell {

class shellCommandClipboard {
 public:
  // Constructor: init (resolve) command and arguments
  shellCommandClipboard(int argc, const std::vector<std::string>& argv);

  virtual ~shellCommandClipboard();

  static bool appendClipboardToFile(std::string path_file);
  static bool saveClipboardToFile(std::string path_file);

 private:
  int argc_;
  std::vector<std::string> argv_;
};

}  // namespace doShell

#endif  // DOSHELL_DOSH_SHELL_COMMAND_SHELL_COMMAND_CLIPBOARD_H_
