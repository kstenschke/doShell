// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#include <doShell/app/app_argument.h>

#include <utility>

namespace doShell {

// Constructor
AppArgument::AppArgument(
    int argc, std::vector<std::string>  argv)
    : argc_(argc), argv_(std::move(argv)) {
}

// Resolve path from given argument:
// keep absolute or make relative from execution path
std::string AppArgument::ResolvePathFromArgument(
    const std::string& pwd,
    int argc,
    const std::vector<std::string>& argv,
    int index_argument,
    bool must_exist) {
  std::string path;

  if (argc >= index_argument) {
    path = argv[index_argument - 1];
    helper::File::ResolvePath(pwd, &path);
  } else {
    AppLog::NotifyError("Missing file argument");
  }

  if (!must_exist
      || path.empty()
      || helper::File::FileExists(path)) return path;

  doShell::AppLog::NotifyError("File not found: " + path);

  return "";
}

}  // namespace doShell
