// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#ifndef DOSHELL_DOSH_SHELLCOMMAND_SHELLCOMMANDURLPARSER_H_
#define DOSHELL_DOSH_SHELLCOMMAND_SHELLCOMMANDURLPARSER_H_

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
#include <thread>  // NOLINT
#include <vector>

namespace doShell {

class shellCommandUrlParser {
 public:
  // Constructor: init (resolve) command and arguments
  shellCommandUrlParser(int argc, const std::vector<std::string>& argv);

  virtual ~shellCommandUrlParser();

  // Extract scheme from given URL, e.g. http or https
  bool GetSchemeFromUrl() const;

  // Extract host from given URL, e.g. www.example.com
  bool GetHostFromUrl() const;

  // Extract path from given URL, e.g. /foo/bar
  bool GetPathFromUrl() const;

  // Extract query from given URL, e.g. hat=bowler&accessory=cane
  bool GetQueryFromUrl() const;

 private:
  int argc_;
  std::vector<std::string> argv_;
};

}  // namespace doShell

#endif  // DOSHELL_DOSH_SHELLCOMMAND_SHELLCOMMANDURLPARSER_H_
