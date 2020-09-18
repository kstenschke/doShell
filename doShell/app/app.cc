// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#include <doShell/app/app.h>

namespace doShell {

// Constructor: init (resolve) command and arguments
App::App(int argc, const std::vector<std::string>& argv) {
  if (argv.size() == 1) {
    // No command given
    AppHelp::PrintHelp(true, AppCommands::Command::Command_Invalid);

    return;
  }

  argc_ = argc;
  argv_ = argv;

  command_ = new AppCommands(argc > 0 ? argv[1] : "");
}

App::~App() {
  delete command_;
}

bool App::Process() {
  AppCommands::Command command = command_->GetResolved();

  bool result;

  if (AppCommands::IsStringManipulationCommand(command)) {
    result = ProcessStringCommand(command);
  } else if (AppCommands::IsUrlParserCommand(command)) {
    result = ProcessUrlParserCommand(command);
  } else if (AppCommands::IsTranspilerCommand(command)) {
    result = ProcessTranspilerCommand(command);
  } else if (AppCommands::IsClipboardCommand(command)) {
    result = ProcessClipboardCommand(command);
  } else {
    switch (command) {
      case AppCommands::Command_Help: {  // h - output help
        AppCommands::Command kCommand;
        std::string command_identifier;

        if (argc_ > 2) {
          kCommand = AppCommands::ResolveCommandByName(argv_[2]);
          command_identifier = argv_[2];
        } else {
          kCommand = AppCommands::Command_Invalid;
        }

        result = AppHelp::PrintHelp(true, kCommand, command_identifier);
      }
        break;
      case AppCommands::Command_Version:  // v - output version
        result = AppHelp::PrintVersion();
        break;
      case AppCommands::Command_Invalid:
      default:AppHelp::PrintUnknownArgumentMessage(argv_[1]);
        result = false;
    }
  }

  return result;
}

bool App::ProcessStringCommand(AppCommands::Command command) {
  bool result;
  auto *StringCommands = new shellCommandString(argc_, argv_);

  switch (command) {
    case AppCommands::Command_ReplaceAfter:  // replaceAfter
      result = StringCommands->ReplaceAfter();

      break;
    case AppCommands::Command_ReplaceAll:  // replaceAll
      result = StringCommands->ReplaceAll();

      break;
    case AppCommands::Command_ReplaceBefore:  // replaceBefore
      result = StringCommands->ReplaceBefore();

      break;
    case AppCommands::Command_ReplaceBetween:  // replaceBetween
      result = StringCommands->ReplaceBetween();

      break;
    case AppCommands::Command_ExtractBetween:  // extractBetween
      result = StringCommands->ExtractBetween();

      break;    case AppCommands::Command_ReplaceFirst:  // replaceFirst
      result = StringCommands->ReplaceFirst();

      break;
    default:
      return false;
  }

  delete StringCommands;

  return result;
}

bool App::ProcessClipboardCommand(AppCommands::Command command) {
  switch (command) {
    case AppCommands::Command_AppendClipboardToFile: {
      // appendClipboardToFile
      std::string path_file = argv_[2];

      return shellCommandClipboard::appendClipboardToFile(path_file);
    }
    case AppCommands::Command_SaveClipboardToFile: {  // saveClipboardToFile
      std::string path_file = argv_[2];

      return shellCommandClipboard::saveClipboardToFile(path_file);
    }
    default:
      return false;
  }
}

bool App::ProcessTranspilerCommand(AppCommands::Command command) {
  bool result;

  auto compiler = new S2sTranspiler(argc_, argv_);
  result = compiler->Compile(command == AppCommands::Command_RunClean);

  switch (command) {
    case AppCommands::Command_Compile: {  // c - compile
      delete compiler;

      return result;
    }
    case AppCommands::Command_Run:case AppCommands::Command_RunClean: {
      // r - transpile (if intermediary transpiled file exists: skip) and run
      // rc - transpile (if intermediary transpiled file exists: overwrite) and run
      if (!result) {
        delete compiler;

        return false;
      }

      result = compiler->Execute();

      delete compiler;

      return result;
    }
    default:
      return false;
  }
}

bool App::ProcessUrlParserCommand(AppCommands::Command command) {
  bool result = false;
  auto *UrlParser = new shellCommandUrl(argc_, argv_);

  switch (command) {
    case AppCommands::Command_GetSchemeFromUrl:  // getSchemeFromUrl
      result = UrlParser->GetSchemeFromUrl();

      break;
    case AppCommands::Command_GetHostFromUrl:  // getHostFromUrl
      result = UrlParser->GetHostFromUrl();

      break;
    case AppCommands::Command_GetPathFromUrl:  // getPathFromUrl
//      result = StringCommands->ReplaceBefore();

      break;
    case AppCommands::Command_GetQueryFromUrl:  // getQueryFromUrl
      result = UrlParser->GetQueryFromUrl();

      break;
    case AppCommands::Command_UrlEncode:  // urlEncode
      result = UrlParser->Encode();

      break;
    case AppCommands::Command_UrlDecode:  // urlDecode
      result = UrlParser->Encode();

      break;
    default:
      result = false;
  }

  delete UrlParser;

  return result;
}

}  // namespace doShell
