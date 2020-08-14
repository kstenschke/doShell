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
  if (command == "extractBetween") return Command_ExtractBetween;
  if (command == "replaceAll") return Command_ReplaceAll;
  if (command == "replaceAfter") return Command_ReplaceAfter;
  if (command == "replaceBefore") return Command_ReplaceBefore;
  if (command == "replaceFirst") return Command_ReplaceFirst;
  if (command == "replaceLast") return Command_ReplaceLast;
  if (command == "-r" || command == "run")
    return Command_Run;
  if (command == "saveClipboardToFile")
    return Command_SaveClipboardToFile;
  if (command == "-h" || command == "help" || command == "?")
    return Command_Help;
  if (command == "-v" || command == "version") return Command_Version;

  return Command_Invalid;
}

bool AppCommands::IsStringManipulationCommand(AppCommands::Command command) {
  switch (command) {
    case Command_ExtractBetween:
    case Command_ReplaceAll:
    case Command_ReplaceAfter:
    case Command_ReplaceBefore:
    case Command_ReplaceFirst:
    case Command_ReplaceLast:
      return true;
    default:
      return false;
  }
}

}  // namespace doShell
