// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#include <doShell/app/app.h>
#include <doShell/dosh/runtime.h>

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

void App::SetPathIn(const std::string &path_docx_in) {
  path_in_ = path_docx_in;
}

void App::SetPathOut(const std::string &path_docx_out) {
  path_out_ = path_docx_out;
}

bool App::Process() {
  auto arguments = new AppArgument(argc_, argv_);

  AppCommands::Command command = command_->GetResolved();

  bool result;

    switch (command) {
      case AppCommands::Command_Compile: {  // c - compile
        auto compiler = new Compiler(argc_, argv_);
        result = compiler->Compile();

        delete compiler;

        return result;
      }
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
      case AppCommands::Command_Run: {  // r - compile and run
        auto compiler = new Compiler(argc_, argv_);
        result = compiler->Compile();

        if (!result) {
          delete compiler;

          return false;
        }

        result = compiler->Execute();

        delete compiler;

        return result;
      }
      case AppCommands::Command_SaveClipboardToFile:  // saveClipboardToFile
        result = AppHelp::PrintVersion();
        break;
      case AppCommands::Command_Version:  // v - output version
        result = AppHelp::PrintVersion();
        break;
      case AppCommands::Command_Invalid:
      default:AppHelp::PrintUnknownArgumentMessage(argv_[1]);
        result = false;
    }


  delete arguments;

  return result;
}

}  // namespace doShell
