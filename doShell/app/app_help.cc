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
    case AppCommands::Command_ListFields:
    case AppCommands::Command_ListFieldsAsJson:
      return PrintHelpOnListMergeFields(true);

    case AppCommands::Command_ListMeta:
    case AppCommands::Command_ListMetaAsJson:return PrintHelpOnListMeta(true);

    case AppCommands::Command_Invalid:
      if (!command_identifier.empty()) {
        docxbox::AppLog::NotifyError("Unknown command: " + command_identifier);

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
      "\n  List DOCX contents:"
          "\n    ls    - Output list of files in DOCX"
          "\n    lsj   - Output list of files in DOCX as JSON"
          "\n    lsf   - Output list of fonts in DOCX"
          "\n    lsfj  - Output list of fonts in DOCX as JSON"
          "\n    lsd   - Output list of fields in DOCX"
          "\n    lsdj  - Output list of fields in DOCX as JSON"
          "\n    lsi   - Output list of images in DOCX"
          "\n    lsij  - Output list of images in DOCX as JSON"
          "\n    lsl   - Output list of files containing given string"
          "\n    lsm   - Output DOCX meta of data"
          "\n    lsmj  - Output DOCX meta data as JSON"
          "\n"
          "\n  Convert and compare DOCX:"
          "\n    cat   - Output content of file contained within DOCX"
          "\n    txt   - Output DOCX document as plaintext"
          "\n    diff  - Side-by-side compare file from two DOCX "
          "archives"
          "\n"
          "\n  Meta commands:"
          "\n    h     - Help: Describe usage of this program"
          "\n    v     - Version: Output version number"
          "\n\n"
          "Type 'docxbox help <command>' "
          "for more help on a specific command."
          "\n\n";

  std::string column_2 =
      "\n  Manipulate DOCX document:"
          "\n    rpi   - Replace image in DOCX"
          "\n    rpt   - Replace text in DOCX"
          "\n    rmt   - Remove DOCX content between given strings"
          "\n    mm    - Modify or set meta attribute in DOCX"
          "\n    sfv   - Set field value"
          "\n    lorem - Replace all text by random dummy text"
          "\n"
          "\n  Batch process multiple docxBox commands on DOCX:"
          "\n    batch"
          "\n"
          "\n  Execute user-defined command on contained file(s) of DOCX:"
          "\n    cmd"
          "\n"
          "\n  Extract and create DOCX:"
          "\n    uz    - Unzip files from DOCX"
          "\n    uzi   - Unzip DOCX and indent XML files"
          "\n    uzm   - Unzip only media files from DOCX"
          "\n    zp    - Create (zip) DOCX from files"
          "\n    zpc   - Compress XML, than create DOCX from files";

  std::cout << helper::String::RenderTwoColumns(column_1, column_2);

  return true;
}

bool AppHelp::PrintHelpOnVersion() {
  std::cout << "Command: v - Output docxBox version number:\n"
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
