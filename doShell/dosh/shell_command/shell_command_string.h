// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#ifndef DOSHELL_DOSH_SHELL_COMMAND_SHELL_COMMAND_STRING_H_
#define DOSHELL_DOSH_SHELL_COMMAND_SHELL_COMMAND_STRING_H_

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

class shellCommandString {
 public:
  // Constructor: init (resolve) command and arguments
  shellCommandString(int argc, const std::vector<std::string>& argv);

  virtual ~shellCommandString();

  // Extract text excluding but between "before" and "after"
  bool ExtractBetween() const;

  // Replace everything after and including
  // the first occurrences of given string
  bool ReplaceAfter() const;

  // Replace all occurrences of given string
  bool ReplaceAll() const;

  // Replace everything before and including
  // the first occurrences of given string
  bool ReplaceBefore() const;

  // Replace text including and between "before" and "after"
  bool ReplaceBetween() const;

  // Replace first occurrence of given string
  bool ReplaceFirst() const;

  // Replace last occurrence of given string
  bool ReplaceLast() const;

 private:
  int argc_;
  std::vector<std::string> argv_;
};

}  // namespace doShell

#endif  // DOSHELL_DOSH_SHELL_COMMAND_SHELL_COMMAND_STRING_H_
