// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#include <doShell/compiler/transpileKeystrokes.h>

namespace doShell {
  bool transpileKeystrokes::TranspileCopy(std::string *code, bool is_linux) {
    return helper::String::ReplaceAll(
        code,
        "#copy",
        is_linux
        ? "xdotool key ctrl+c"
        : "osascript -e 'tell application \"System Events\" to keystroke \"c\" "
          "using command down'") > 0;
  }

  bool transpileKeystrokes::TranspileCut(std::string *code, bool is_linux) {
    return helper::String::ReplaceAll(
        code,
        "#cut",
        is_linux
        ? "xdotool key ctrl+x"
        : "osascript -e 'tell application \"System Events\" to keystroke \"x\" "
          "using command down'") > 0;
  }

  bool transpileKeystrokes::TranspilePaste(std::string *code, bool is_linux) {
    return helper::String::ReplaceAll(
        code,
        "#paste",
        is_linux
        ? "xdotool key ctrl+v"
        : "osascript -e 'tell application \"System Events\" to keystroke \"v\" "
          "using command down'") > 0;
  }

  bool transpileKeystrokes::TranspileSelectAll(std::string *code,
                                               bool is_linux) {
    return helper::String::ReplaceAll(
        code,
        "#selectAll",
        is_linux
        ? "xdotool key ctrl+a"
        : "osascript -e 'tell application \"System Events\" to keystroke \"a\" "
          "using command down'") > 0;
  }

  bool transpileKeystrokes::TranspileHitKey(std::string *code, bool is_linux) {
    bool replaced = helper::String::ReplaceAll(
        code,
        "#hit enter",
        is_linux
        ? "xdotool key KP_Enter"
        : "osascript -e 'tell application \"System Events\" "
          "to key code 36'") > 0;

    return replaced;
  }
}  // namespace doShell
