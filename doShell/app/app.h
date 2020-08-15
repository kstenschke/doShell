// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#ifndef DOSHELL_APP_APP_H_
#define DOSHELL_APP_APP_H_

#include <doShell/app/app_argument.h>
#include <doShell/app/app_command.h>
#include <doShell/app/app_help.h>
#include <doShell/config.h>
#include <doShell/dosh/runtime.h>
#include <doShell/dosh/shellCommand/shellCommandClipboard.h>
#include <doShell/dosh/shellCommand/shellCommandString.h>
#include <doShell/dosh/shellCommand/shellCommandUrlParser.h>
#include <doShell/helper/helper_dateTime.h>

#include <cstring>
#include <iostream>
#include <string>
#include <vector>

namespace doShell {

class App {
 public:
  // Meta constants
  static const std::string kAppName;
  static const std::string kAppExecutableName;

  // Constructor: init (resolve) command and arguments
  App(int argc, const std::vector<std::string>& argv);

  virtual ~App();

  void SetPathIn(const std::string &path_docx_in);
  void SetPathOut(const std::string &path_docx_out);

  // Process command + arguments
  bool Process();

 private:
  int argc_;
  std::vector<std::string> argv_;

  AppCommands *command_ = nullptr;

  std::string path_in_;
  std::string path_out_;  // Output path with/or filename

  bool ProcessStringCommand(AppCommands::Command command);
  bool ProcessUrlParserCommand(AppCommands::Command command);
};

}  // namespace doShell

#endif  // DOSHELL_APP_APP_H_
