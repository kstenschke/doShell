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
  } else if (AppCommands::IsFileManipulationCommand(command)) {
    result = ProcessFileCommand(command);
  } else if (AppCommands::IsUrlParserCommand(command)) {
    result = ProcessUrlParserCommand(command);
  } else if (AppCommands::IsTranspilerCommand(command)) {
    result = ProcessTranspilerCommand(command);
  } else if (AppCommands::IsClipboardCommand(command)) {
    result = ProcessClipboardCommand(command);
  } else {
    switch (command) {
      case AppCommands::Command_Help: {
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
      case AppCommands::Command_Version:
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
    case AppCommands::Command_ReplaceAfter:
      result = StringCommands->ReplaceAfter();

      break;
    case AppCommands::Command_ReplaceAll:
      result = StringCommands->ReplaceAll();

      break;
    case AppCommands::Command_ReplaceBefore:
      result = StringCommands->ReplaceBefore();

      break;
    case AppCommands::Command_ReplaceBetween:
      result = StringCommands->ReplaceBetween();

      break;
    case AppCommands::Command_ExtractBetween:
      result = StringCommands->ExtractBetween();

      break;
    case AppCommands::Command_ReplaceFirst:
      result = StringCommands->ReplaceFirst();

      break;
    case AppCommands::Command_ReplaceLast:
      result = StringCommands->ReplaceLast();

      break;
    default:
      result = false;
  }

  delete StringCommands;

  return result;
}

bool App::ProcessFileCommand(AppCommands::Command command) {
  bool result;
  auto *StringCommands = new shellCommandString(argc_, argv_);

  std::string file_content;
  auto is_loaded = helper::File::GetFileContents(argv_[2], &file_content);

  if (!is_loaded || file_content.empty()) {
    delete StringCommands;

    return false;
  }

  switch (command) {
    case AppCommands::Command_ReplaceAfterFromFile:
      result = StringCommands->ReplaceAfter(file_content);

      break;
    case AppCommands::Command_ReplaceAllFromFile:
      result = StringCommands->ReplaceAll(file_content);

      break;
    case AppCommands::Command_ReplaceBeforeFromFile:
      result = StringCommands->ReplaceBefore(file_content);

      break;
    case AppCommands::Command_ReplaceBetweenFromFile:
      result = StringCommands->ReplaceBetween(file_content);

      break;
    case AppCommands::Command_ExtractBetweenFromFile:
      result = StringCommands->ExtractBetween(file_content);

      break;
    case AppCommands::Command_ReplaceFirstFromFile:
      result = StringCommands->ReplaceFirst(file_content);

      break;
    case AppCommands::Command_ReplaceLastFromFile:
      result = StringCommands->ReplaceLast(file_content);

      break;
    default:
      result = false;
  }

  delete StringCommands;

  return result;
}

bool App::ProcessClipboardCommand(AppCommands::Command command) {
  bool result;
  auto *ClipboardCommands = new shellCommandClipboard(argc_, argv_);

  switch (command) {
    // TODO(kay): add commands

    case AppCommands::Command_AppendClipboardToFile: {
      std::string path_file = argv_[2];

      result = shellCommandClipboard::AppendClipboardToFile(path_file);

      break;
    }
    case AppCommands::Command_AppendToClipboard: {
      std::string str;
      clip::get_text(str);

      result = shellCommandClipboard::SetClipboard(str + argv_[2]);

      break;
    }
    case AppCommands::Command_ExtractBetweenFromClipboard: {
      result = ClipboardCommands->ExtractBetween();

      break;
    }
    case AppCommands::Command_GetClipboard: {
      std::string str;
      clip::get_text(str);

      std::cout << str;

      result = true;

      break;
    }
    case AppCommands::Command_LoadIntoClipboard: {
      std::string str;
      helper::File::GetFileContents(argv_[2], &str);

      result = shellCommandClipboard::SetClipboard(str);

      break;
    }
    case AppCommands::Command_PrependToClipboard: {
      std::string str;
      clip::get_text(str);

      result = shellCommandClipboard::SetClipboard(argv_[2] + str);

      break;
    }
    case AppCommands::Command_PasteRenderedFromFile: {
      result = argc_ < 3
               ? false
               : shellCommandClipboard::PasteRenderedFromFile(argv_[2],
                                                              argv_[3]);
      break;
    }
    case AppCommands::Command_PregMatchAllFromClipboard: {
      result = shellCommandClipboard::PregMatchAll(argv_[2]);

      break;
    }
    case AppCommands::Command_ReplaceAfterFromClipboard: {
      result = ClipboardCommands->ReplaceAfter();

      break;
    }
    case AppCommands::Command_ReplaceAllFromClipboard: {
      result = ClipboardCommands->ReplaceAll();

      break;
    }
    case AppCommands::Command_ReplaceBeforeFromClipboard: {
      result = ClipboardCommands->ReplaceBefore();

      break;
    }
    case AppCommands::Command_ReplaceBetweenFromClipboard: {
      result = ClipboardCommands->ReplaceBetween();

      break;
    }
    case AppCommands::Command_ReplaceFirstFromClipboard: {
      result = ClipboardCommands->ReplaceFirst();

      break;
    }
    case AppCommands::Command_ReplaceLastFromClipboard: {
      result = ClipboardCommands->ReplaceLast();

      break;
    }
    case AppCommands::Command_SaveClipboardToFile: {
      std::string path_file = argv_[2];

      result = shellCommandClipboard::SaveClipboardToFile(path_file);

      break;
    }
    case AppCommands::Command_SetClipboard: {
      result = shellCommandClipboard::SetClipboard(argv_[2]);

      break;
    }
    case AppCommands::Command_SetClipboardFromFile: {
      std::string str;
      helper::File::GetFileContents(argv_[2], &str);

      result = shellCommandClipboard::SetClipboard(str);

      break;
    }
    default:
      result = false;
  }

  delete ClipboardCommands;

  return result;
}

bool App::ProcessTranspilerCommand(AppCommands::Command command) {
  bool result;

  auto compiler = new S2sTranspiler(argc_, argv_);
  result = compiler->Compile(command == AppCommands::Command_RunClean);

  switch (command) {
    case AppCommands::Command_Compile: {
      delete compiler;

      return result;
    }
    case AppCommands::Command_Run:case AppCommands::Command_RunClean: {
      // r - transpile (if transpiled file exists: skip) and run
      // rc - transpile (if transpiled file exists: overwrite) and run
      if (!result) {
        delete compiler;

        return false;
      }

      result = compiler->Execute();

      compiler->RemoveIntermediaryCode();

      delete compiler;

      return result;
    }
    default:
      delete compiler;

      return false;
  }
}

bool App::ProcessUrlParserCommand(AppCommands::Command command) {
  bool result;
  auto *UrlParser = new shellCommandUrl(argc_, argv_);

  switch (command) {
    case AppCommands::Command_GetSchemeFromUrl:
      result = UrlParser->GetSchemeFromUrl();

      break;
    case AppCommands::Command_GetHostFromUrl:
      result = UrlParser->GetHostFromUrl();

      break;
    case AppCommands::Command_GetPathFromUrl:
      result = UrlParser->GetPathFromUrl();

      break;
    case AppCommands::Command_GetQueryFromUrl:
      result = UrlParser->GetQueryFromUrl();

      break;
    case AppCommands::Command_UrlEncode:
      result = UrlParser->Encode();

      break;
    case AppCommands::Command_UrlDecode:
      result = UrlParser->Encode();

      break;
    default:
      result = false;
  }

  delete UrlParser;

  return result;
}

}  // namespace doShell
