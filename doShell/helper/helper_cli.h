// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#ifndef DOSHELL_HELPER_HELPER_CLI_H_
#define DOSHELL_HELPER_HELPER_CLI_H_

#include <doShell/helper/helper_numeric.h>

#ifdef __linux__
  #include <sys/sendfile.h>
#elif _WIN32
  // windows code goes here
#else
  // Mac OS
  #include <sys/types.h>
  #include <sys/socket.h>
  #include <sys/uio.h>
#endif

#include <fcntl.h>
#include <algorithm>
#include <codecvt>
#include <cstring>
#include <cmath>
#include <functional>
#include <locale>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace helper {
namespace Cli {

extern void Execute(const char *command);
extern std::string GetExecutionResponse(const char *command);

}  // namespace Cli
}  // namespace helper

#endif  // DOSHELL_HELPER_HELPER_CLI_H_
