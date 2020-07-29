// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#include <doShell/compiler/transpileControlFlow.h>

namespace doShell {
bool transpileControlFlow::TranspileWait(std::string *code, bool is_linux) {
//  return helper::String::ReplaceAll(
//      code,
//      "#wait",
//      is_linux
//      ? "xdotool key ctrl+c"
//      : "osascript -e 'tell application \"System Events\" to keystroke \"c\" "
//        "using command down'"
//  ) > 0;
  return false;
}
}  // namespace doShell
