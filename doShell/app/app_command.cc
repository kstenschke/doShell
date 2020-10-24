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
  if (command == "appendClipboardToFile") return Command_AppendClipboardToFile;
  if (command == "appendToClipboard") return Command_AppendToClipboard;
  if (command == "compile" || command == "-c") return Command_Compile;
  if (command == "extractBetween") return Command_ExtractBetween;
  if (command == "extractBetweenFromFile") return Command_ExtractBetweenFromFile;
  if (command == "extractBetweenFromClipboard") return
        Command_ExtractBetweenFromClipboard;
  if (command == "getHostFromUrl") return Command_GetHostFromUrl;
  if (command == "getPathFromUrl") return Command_GetPathFromUrl;
  if (command == "getQueryFromUrl") return Command_GetQueryFromUrl;
  if (command == "getSchemeFromUrl") return Command_GetSchemeFromUrl;
  if (command == "loadIntoClipboard") return Command_LoadIntoClipboard;
  if (command == "pregMatchAllInClipboard")
    return Command_PregMatchAllInClipboard;
  if (command == "prependToClipboard") return Command_PrependToClipboard;
  if (command == "replaceAfter") return Command_ReplaceAfter;
  if (command == "replaceAll") return Command_ReplaceAll;
  if (command == "replaceAllInnClipboard") return Command_ReplaceAllInClipboard;
  if (command == "replaceAllInClipboard") return Command_ReplaceAllInClipboard;
  if (command == "replaceBefore") return Command_ReplaceBefore;
  if (command == "replaceBeforeInClipboard") return Command_ReplaceBeforeInClipboard;
  if (command == "replaceBetween") return Command_ReplaceBetween;
  if (command == "replaceBetweenInClipboard") return Command_ReplaceBetweenInClipboard;
  if (command == "replaceFirst") return Command_ReplaceFirst;
  if (command == "replaceFirstInClipboard")
    return Command_ReplaceFirstInClipboard;
  if (command == "replaceLast") return Command_ReplaceLast;
  if (command == "replaceAfterFromFile") return Command_ReplaceAfterFromFile;
  if (command == "replaceAllFromFile") return Command_ReplaceAllFromFile;
  if (command == "replaceBeforeFromFile") return Command_ReplaceBeforeFromFile;
  if (command == "replaceFirstFromFile") return Command_ReplaceFirstFromFile;
  if (command == "replaceLastFromFile") return Command_ReplaceLastFromFile;
  if (command == "replaceLastInClipboard") return Command_ReplaceLastInClipboard;
  if (command == "replaceBetweenFromFile") return Command_ReplaceBetweenFromFile;
  if (command == "run" || command == "-r") return Command_Run;
  if (command == "runClean" || command == "-rc") return Command_RunClean;
  if (command == "saveClipboard") return Command_SaveClipboardToFile;
  if (command == "setClipboard") return Command_SetClipboard;
  if (command == "setClipboardFromFile") return Command_SetClipboardFromFile;
  if (command == "urlEncode") return Command_UrlEncode;
  if (command == "urlDecode") return Command_UrlDecode;
  if (command == "help" || command == "-h" || command == "?")
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
    case Command_ReplaceBetween:
    case Command_ReplaceFirst:
    case Command_ReplaceLast:
      return true;
    default:
      return false;
  }
}

bool AppCommands::IsFileManipulationCommand(AppCommands::Command command) {
  switch (command) {
    case Command_ExtractBetweenFromFile:
    case Command_ReplaceAllFromFile:
    case Command_ReplaceAfterFromFile:
    case Command_ReplaceBeforeFromFile:
    case Command_ReplaceBetweenFromFile:
    case Command_ReplaceFirstFromFile:
    case Command_ReplaceLastFromFile:
      return true;
    default:
      return false;
  }
}

bool AppCommands::IsUrlParserCommand(AppCommands::Command command) {
  switch (command) {
    case Command_GetSchemeFromUrl:
    case Command_GetHostFromUrl:
    case Command_GetPathFromUrl:
    case Command_GetQueryFromUrl:
    case Command_UrlEncode:
    case Command_UrlDecode:
      return true;
    default:
      return false;
  }
}

bool AppCommands::IsTranspilerCommand(AppCommands::Command command) {
  switch (command) {
    case Command_Compile:
    case Command_Run:
    case Command_RunClean:
      return true;
    default:
      return false;
  }
}

bool AppCommands::IsClipboardCommand(AppCommands::Command command) {
  switch (command) {
    case Command_AppendClipboardToFile:
    case Command_AppendToClipboard:
    case Command_ExtractBetweenFromClipboard:
    case Command_LoadIntoClipboard:
    case Command_PregMatchAllInClipboard:
    case Command_PrependToClipboard:
    case Command_ReplaceAfterInClipboard:
    case Command_ReplaceAllInClipboard:
    case Command_ReplaceBeforeInClipboard:
    case Command_ReplaceBetweenInClipboard:
    case Command_ReplaceFirstInClipboard:
    case Command_ReplaceLastInClipboard:
    case Command_SaveClipboardToFile:
    case Command_SetClipboard:
    case Command_SetClipboardFromFile:
      return true;
    default:
      return false;
  }
}

}  // namespace doShell
