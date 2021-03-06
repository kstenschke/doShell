// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#ifndef DOSHELL_DOSH_SHELL_COMMAND_SHELL_COMMAND_URL_H_
#define DOSHELL_DOSH_SHELL_COMMAND_SHELL_COMMAND_URL_H_

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

class shellCommandUrl {
 public:
  // Constructor: init (resolve) command and arguments
  shellCommandUrl(int argc, const std::vector<std::string>& argv);

  virtual ~shellCommandUrl();

  // Extract scheme from given URL, e.g. http or https
  bool GetSchemeFromUrl() const;

  // Extract host from given URL, e.g. www.example.com
  bool GetHostFromUrl() const;

  // Extract path from given URL, e.g. /foo/bar
  bool GetPathFromUrl() const;

  // Extract query from given URL, e.g. hat=bowler&accessory=cane
  bool GetQueryFromUrl() const;

  bool Decode();
  bool Encode();

 private:
  int argc_;
  std::vector<std::string> argv_;

  void GetPathFromUrl(std::string *url) const;
};

}  // namespace doShell

#endif  // DOSHELL_DOSH_SHELL_COMMAND_SHELL_COMMAND_URL_H_
