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

  for (int index = 0; index < argc; ++index)
    arguments.emplace_back(argv[index]);

  doShell::AppLog::LogStartUp(arguments);

  // Process command arguments, display help if no valid command given
  auto *app = new doShell::App(arguments.size(), arguments);

  bool success = argc > 1
                 ? app->Process()
                 : false;

  // TODO(kay): return comprehensible bash error codes instead of 125
  int return_signal = success ? 0 : 125;

  doShell::AppLog::NotifyInfo(
      "doShell finished w/ return code: " + std::to_string(return_signal),
      true);

  doShell::AppLog::Output();

  delete app;

  return return_signal;
}
