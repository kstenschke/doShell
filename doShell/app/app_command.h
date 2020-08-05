// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#ifndef DOSHELL_APP_APP_COMMAND_H_
#define DOSHELL_APP_APP_COMMAND_H_

#include <string>
#include <utility>

namespace doShell {

class AppCommands {
 public:
  enum Command {
    Command_Compile,
    Command_Help,
    Command_Run,
    Command_AppendClipboardToFile,
    Command_SaveClipboardToFile,
    Command_Version,
    Command_Invalid
  };

  explicit AppCommands(std::string argc);

  static Command ResolveCommandByName(const std::string &command);

  Command GetResolved();

 private:
  // Argument value as received from CLI
  std::string argc_;

  // Argument resolved to Commands-enum
  Command resolved_;

  // Resolve command (1st argument) to rel. command enum item, allowing switch
  Command Resolve();
};

}  // namespace doShell

#endif  // DOSHELL_APP_APP_COMMAND_H_
