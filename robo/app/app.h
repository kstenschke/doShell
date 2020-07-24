// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#ifndef DOCXBOX_APP_APP_H_
#define DOCXBOX_APP_APP_H_

#include <robo/app/app_argument.h>
#include <robo/app/app_command.h>
#include <robo/app/app_help.h>
#include <robo/config.h>
#include <robo/helper/helper_dateTime.h>

#include <cstring>
#include <iostream>
#include <string>
#include <vector>

namespace robo {

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

  bool is_batch_mode_ = false;

  AppCommands *command_ = nullptr;

  std::string path_out_;  // Output path with/or filename

  AppCommands::Command PreProcess(AppArgument *arguments,
                                  const AppCommands::Command &command) const;
};

}  // namespace docxbox

#endif  // DOCXBOX_APP_APP_H_
