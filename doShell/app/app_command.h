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
    Command_AppendClipboardToFile,
    Command_Compile,
    Command_ExtractBetween,
    Command_GetSchemeFromUrl,
    Command_GetHostFromUrl,
    Command_GetPathFromUrl,
    Command_GetQueryFromUrl,
    Command_Help,
    Command_Invalid,
    Command_ReplaceAll,
    Command_ReplaceAfter,
    Command_ReplaceBefore,
    Command_ReplaceBetween,
    Command_ReplaceFirst,
    Command_ReplaceLast,
    Command_Run,
    Command_SaveClipboardToFile,
    Command_UrlEncode,
    Command_UrlDecode,
    Command_Version
  };

  explicit AppCommands(std::string argc);

  static Command ResolveCommandByName(const std::string &command);

  static bool IsStringManipulationCommand(AppCommands::Command command);
  static bool IsUrlParserCommand(AppCommands::Command command);
  static bool IsTranspilerCommand(AppCommands::Command command);
  static bool IsClipboardCommand(AppCommands::Command command);

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
