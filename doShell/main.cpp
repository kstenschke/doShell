// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#include <doShell/app/app.h>

/**
 * @param argc Amount of arguments
 * @param argv Array of arguments, argv[0] is name and path of executable
 */
int main(int argc, char **argv) {
  std::vector<std::string> arguments;
  arguments.reserve(argc);

//  argc = 3;
//  argv[1] = "-rc";
//  argv[2] =
//      "/Users/kay/CLionProjects/robo/examples/006_file_manipulation.do.sh";

  for (int index = 0; index < argc; ++index)
    arguments.emplace_back(argv[index]);

  // Process command arguments, display help if no valid command given
  auto *app = new doShell::App(arguments.size(), arguments);

  bool success = argc > 1
                 ? app->Process()
                 : false;

  int return_signal = success ? 0 : 125;

  delete app;

  return return_signal;
}
