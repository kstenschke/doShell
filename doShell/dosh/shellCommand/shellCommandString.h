// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#ifndef DOSHELL_DOSH_SHELLCOMMAND_SHELLCOMMANDSTRING_H_
#define DOSHELL_DOSH_SHELLCOMMAND_SHELLCOMMANDSTRING_H_

#include <doShell/app/app_argument.h>
#include <doShell/app/app_command.h>
#include <doShell/app/app_help.h>
#include <doShell/config.h>
#include <doShell/dosh/transpile/transpileClipboard.h>
#include <doShell/dosh/transpile/transpileBrowser.h>
#include <doShell/dosh/transpile/transpileKeystrokes.h>
#include <doShell/helper/helper_cli.h>

#include <cstring>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

namespace doShell {

class shellCommandString {
 public:
  // Constructor: init (resolve) command and arguments
  shellCommandString(int argc, const std::vector<std::string>& argv);

  virtual ~shellCommandString();

  bool ExtractBetween() const;

  bool ReplaceAll() const;

  // Replace everything before and including the first occurrences of given string
  bool ReplaceBefore() const;

  bool ReplaceFirst() const;

 private:
  int argc_;
  std::vector<std::string> argv_;
};

}  // namespace doShell

#endif  // DOSHELL_DOSH_SHELLCOMMAND_SHELLCOMMANDSTRING_H_
