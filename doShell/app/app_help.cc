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
        std::cerr << "Unknown command: " + command_identifier << "\n";

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
      "\n    -c             - Transpile given script file"
      "\n    -r             - Transpile if not yet and run given script file"
      "\n    -rc            - Force transpile and run given script file"
      "\n"
      "\n  Meta commands:"
      "\n    -h             - Help: Describe usage of this program"
      "\n    -v             - Version: Output version number"
      "\n"
      "\n  Commands for string manipulation:"
      "\n    extractBetween - Extract text between strings"
      "\n    replaceAfter   - Replace after and including 1st occurrence of string"
      "\n    replaceAll     - Replace all occurrences of string"
      "\n    replaceBefore  - Replace before and including 1st occurrence of string"
      "\n    replaceBetween - Replace text between and including given strings"
      "\n    replaceFirst   - Replace first occurrence of string"
      "\n    replaceLast    - Replace last occurrence of string"
      "\n"
      "\n    extractBetweenFromFile - Extract text between strings from file"
      "\n    replaceAfterFromFile   - Replace after and including 1st occurrence of string from file"
      "\n    replaceAllFromFile     - Replace all occurrences of string from file"
      "\n    replaceBeforeFromFile  - Replace before and including 1st occurrence of string from file"
      "\n    replaceBetweenFromFile - Replace text between and including given strings from file"
      "\n    replaceFirstFromFile   - Replace first occurrence of string from file"
      "\n    replaceLastFromFile    - Replace last occurrence of string from file"
      "\n\n";

  std::string column_2 =
      "\n  Commands for clipboard/contents manipulation:"
      "\n    appendToClipboard    - Add string to end of clipboard"
      "\n    getClipboard         - Output clipboard contents"
      "\n    prependToClipboard   - Add string before start of clipboard"
      "\n    setClipboard         - Copy string to clipboard"
      "\n    setClipboardFromFile - Copy content of file to clipboard"
      "\n"
      "\n  Commands for URL parsing:"
      "\n    getSchemeFromUrl - Extract scheme from given URL, e.g. http or https"
      "\n    getHostFromUrl   - Extract host from given URL, e.g. www.example.com"
      "\n    getPathFromUrl   - Extract path from given URL, e.g. /foo/bar"
      "\n    getQueryFromUrl  - Extract query from given URL, e.g. hat=bowler"
      "\n    urlEncode        - URL-Encode given string"
      "\n    urlDecode        - URL-Decode given string"
      "\n"
      "\n  Commands for random value generation:"
      "\n    rand <from> <until> - Generate random number between <from> and <until>"
      "\n"
      "\n  For more details on the built-in commands and doShell scripting,"
      "\n  read the documentation at https://github.com/kstenschke/doShell"
      "\n";

  // TODO(kay) list all shell commands

  std::cout << helper::String::RenderTwoColumns(column_1, column_2);

  return true;
}

void AppHelp::PrintUnknownArgumentMessage(const std::string& arg) {
  std::cerr << "Unknown argument: \"" + arg + "\". \n";

  std::cout << "Possible arguments are:\n";

  PrintHelp(false, AppCommands::Command::Command_Invalid);
}

}  // namespace doShell
