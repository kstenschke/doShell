// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#ifndef DOCXBOX_HELPER_HELPER_CLI_H_
#define DOCXBOX_HELPER_HELPER_CLI_H_

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

extern const char ANSI_BOLD[];
extern const char ANSI_DIM[];
extern const char ANSI_UNDERLINE[];
extern const char ANSI_REVERSE[];
extern const char ANSI_RESET[];

extern const char ANSI_LIGHT_GREEN[];
extern const char ANSI_LIGHT_RED[];

extern void Execute(const char *command);
extern std::string GetExecutionResponse(const char *command);

}  // namespace Cli
}  // namespace helper

#endif  // DOCXBOX_HELPER_HELPER_CLI_H_
