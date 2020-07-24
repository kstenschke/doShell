// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#ifndef DOSHELL_APP_APP_HELP_H_
#define DOSHELL_APP_APP_HELP_H_

#include <doShell/config.h>
#include <doShell/app/app.h>

#include <string>
#include <iostream>

namespace doShell {

class AppHelp {
 public:
  static bool PrintVersion();

  static bool PrintHelpOnRun();

  static bool PrintHelp(bool with_title,
                        AppCommands::Command command,
                        const std::string &command_identifier = "");

  static bool PrintHelpOnVersion();

  static bool PrintOverview(bool with_title);

  static void PrintUnknownArgumentMessage(const std::string& arg);
};

}  // namespace doShell

#endif  // DOSHELL_APP_APP_HELP_H_
