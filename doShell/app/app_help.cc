// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#include <doShell/app/app_help.h>

namespace doShell {

bool AppHelp::PrintVersion() {
  std::cout
      << "doShell" << " version "
      << std::string(DOSHELL_VERSION_MAJOR) << "."
      << std::string(DOSHELL_VERSION_MINOR) << "."
      << std::string(DOSHELL_VERSION_PATCH)
      << "\n";

  return true;
}

bool AppHelp::PrintHelp(bool with_title,
                        AppCommands::Command command,
                        const std::string &command_identifier) {
  switch (command) {
//    case AppCommands::Command_ListFields:
//    case AppCommands::Command_ListFieldsAsJson:
//      return PrintHelpOnListMergeFields(true);

    case AppCommands::Command_Invalid:
    default:
      if (!command_identifier.empty()) {
        doShell::AppLog::NotifyError("Unknown command: " + command_identifier);

        with_title = true;
      }

      return PrintOverview(with_title);
  }

  std::cout << "\n\n";

  return true;
}

bool AppHelp::PrintOverview(bool with_title) {
  if (with_title)
    std::cout
        << "doShell v" << DOSHELL_VERSION_MAJOR << "."
        << DOSHELL_VERSION_MINOR << "." << DOSHELL_VERSION_PATCH
        << " - Usage: dosh <command> [args]" << "\n\n"
            "Available commands:\n";

  std::string column_1 =
      "\n  Compile and execute script:"
      "\n    <no arguments> - Find and compile script files recursively"
      "\n                     at current path and its sub directories"
      "\n    -c             - Compile given script file"
      "\n    -r             - Compile and run given script file"
      "\n"
      "\n  Meta commands:"
      "\n    -h             - Help: Describe usage of this program"
      "\n    -v             - Version: Output version number"
      "\n\n"
      "Type 'dosh help <command>' "
      "for more help on a specific command."
      "\n\n";

  std::string column_2 =
      "\n  Built-in shell tools:"
      "\n    replaceAllInFile     - Replace all occurrences of given string in file"
      "\n    replaceFirstInFile   - Replace first occurrence of given string in file"
      "\n    replaceLastInFile    - Replace last occurrence of given string in file"
      "\n    removeBetweenInFile  - Remove text between and including given strings in file"
      "\n    extractBetweenInFile - Save text between (excluding) given strings of given to new file"
      "\n";

  std::cout << helper::String::RenderTwoColumns(column_1, column_2);

  return true;
}

bool AppHelp::PrintHelpOnVersion() {
  std::cout <<
      "Command: v - Output doShell version number:\n"
      "-------------------------------------------\n"
      "  doShell v\n\n";

  return true;
}

void AppHelp::PrintUnknownArgumentMessage(const std::string& arg) {
  AppLog::NotifyError("Unknown argument: \"" + arg + "\". ");

  if (AppLog::IsSilent()) return;

  std::cout << "Possible arguments are:\n";

  PrintHelp(false, AppCommands::Command::Command_Invalid);
}

}  // namespace doShell
