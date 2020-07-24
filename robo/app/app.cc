// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#include <robo/app/app.h>

namespace docxbox {

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
  path_docx_in_ = path_docx_in;
}

void App::SetPathOut(const std::string &path_docx_out) {
  path_docx_out_ = path_docx_out;
}

// Remap command + argument variations to rel. shorthand commands
AppCommands::Command App::PreProcess(
    AppArgument *arguments,
    const AppCommands::Command &command) const {
  switch (command) {
    case AppCommands::Command_Compile:
//      return arguments->Matches(3, "-s", "--segments")
//             ? AppCommands::Command_GetPlainTextSegments
//             : command;
    default:return command;
  }
}

bool App::Process() {
  auto arguments = new AppArgument(argc_, argv_);

  AppCommands::Command command = command_->GetResolved();

  // Preprocess: Remap command + argument(s) to rel. shorthand commands
  if (argc_ > 2) command = PreProcess(arguments, command);

  bool result;



    switch (command) {
      case AppCommands::Command_Compile:
        result = docx_archive->Batch();
        break;
      case AppCommands::Command_Help: {  // h
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
      case AppCommands::Command_Version:  // v
        result = AppHelp::PrintVersion();
        break;
      case AppCommands::Command_Invalid:
      default:AppHelp::PrintUnknownArgumentMessage(argv_[1]);
        result = false;
    }


  delete arguments;

  return result;
}

}  // namespace docxbox
