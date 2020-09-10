// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#include <doShell/app/app.h>

#include <vendor/webview/webview.h>

#ifdef WIN32
int WINAPI WinMain(HINSTANCE hInt, HINSTANCE hPrevInst, LPSTR lpCmdLine,
                   int nCmdShow) {
#endif

/**
 * @param argc Amount of arguments
 * @param argv Array of arguments, argv[0] is name and path of executable
 */
int main(int argc, char **argv) {
  std::vector<std::string> arguments;
  arguments.reserve(argc);

//  argc = 3;
//  argv[1] = "-r";
//  argv[2] =
//      "/home/kay/CLionProjects/shellDo/examples/003_platform_conditions.do.sh";

  webview::webview w(true, nullptr);
  w.set_title("Minimal example");
  w.set_size(480, 320, WEBVIEW_HINT_NONE);
  w.navigate("https://en.m.wikipedia.org/wiki/Main_Page");
  w.run();
  w.terminate();

  for (int index = 0; index < argc; ++index)
    arguments.emplace_back(argv[index]);

  doShell::AppLog::LogStartUp(arguments);

  // Process command arguments, display help if no valid command given
  auto *app = new doShell::App(arguments.size(), arguments);

  bool success = argc > 1
                 ? app->Process()
                 : false;

  int return_signal = success ? 0 : 125;

  doShell::AppLog::NotifyInfo(
      "doShell finished w/ return code: " + std::to_string(return_signal),
      true);

  doShell::AppLog::Output();

  delete app;

  return return_signal;
}
