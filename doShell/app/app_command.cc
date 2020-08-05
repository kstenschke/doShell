// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#include <doShell/app/app_command.h>

namespace doShell {

// Constructor
AppCommands::AppCommands(std::string argc): argc_(std::move(argc)) {
  resolved_ = Resolve();
}

AppCommands::Command AppCommands::GetResolved() {
  return resolved_;
}

// Resolve name of command (1st argument) to related enum item, to allow switch
AppCommands::Command AppCommands::Resolve() {
  return ResolveCommandByName(argc_);
}

AppCommands::Command AppCommands::ResolveCommandByName(
    const std::string &command) {
  if (command == "appendClipboardToFile")
    return Command_AppendClipboardToFile;
  if (command == "-c" || command == "compile")
    return Command_Compile;
  if (command == "-r" || command == "run")
    return Command_Run;
  if (command == "saveClipboardToFile")
    return Command_SaveClipboardToFile;
  if (command == "-h" || command == "help" || command == "?")
    return Command_Help;
  if (command == "-v" || command == "version") return Command_Version;

  return Command_Invalid;
}

}  // namespace doShell
