// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#include <doShell/dosh/runtimeOptions/runtimeOptions.h>

namespace doShell {

bool runtimeOptions::ReplaceRunTimeMacros(std::string *code, bool is_linux) {
  return helper::String::ReplaceAll(
      code,
      "::TIMESTAMP::",
      helper::DateTime::GetTimestamp()) > 0;
}

}  // namespace doShell
