// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#include <doShell/dosh/transpiler/transpileKeystrokes.h>

namespace doShell {
  void transpileKeystrokes::Transpile(std::string *code, bool is_linux) {
    TranspileType(code, is_linux);
    TranspileHitKey(code, is_linux);

    TranspileCopyInTerminal(code, is_linux);
    TranspileCopy(code, is_linux);
    TranspileCut(code, is_linux);
    TranspilePasteInTerminal(code, is_linux);
    TranspilePaste(code, is_linux);
    TranspileSelectAll(code, is_linux);
  }
  
  bool transpileKeystrokes::TranspileCopy(std::string *code, bool is_linux) {
    if (std::string::npos == code->find("#hit copy")) return false;

    return helper::String::ReplaceAll(
        code,
        "#hit copy",
        is_linux
        ? "xdotool key ctrl+c"
        : "osascript -e 'tell application \"System Events\" to keystroke \"c\" "
          "using command down'") > 0;
  }

  bool transpileKeystrokes::TranspileCopyInTerminal(std::string *code, bool is_linux) {
    if (std::string::npos == code->find("#copyInTerminal ")) return false;

    return helper::String::ReplaceAll(
        code,
        "#copyInTerminal",
        is_linux
        ? "xdotool key ctrl+shift+c"
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

  bool transpileKeystrokes::TranspilePasteInTerminal(std::string *code, bool is_linux) {
    if (std::string::npos == code->find("#pasteInTerminal ")) return false;

    return helper::String::ReplaceAll(
        code,
        "#pasteInTerminal",
        is_linux
        ? "xdotool key ctrl+shift+v"
        : "osascript -e 'tell application \"System Events\" to keystroke \"v\" "
          "using command down'") > 0;
  }

  bool transpileKeystrokes::TranspileSelectAll(std::string *code,
                                               bool is_linux) {
    if (std::string::npos == code->find("#selectAll")) return false;

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

bool transpileKeystrokes::TranspileType(std::string *code, bool is_linux) {
  if (is_linux) return helper::String::ReplaceAll(
        code, "#type", "xdotool type ") > 0;

  // mac os:
  /*
   tell application "System Events"
     set textToType to "text here"
     delay 3

     repeat
       delay 1
       keystroke textToType
       keystroke return
     end repeat
   end tell
   */

  return false;
}
}  // namespace doShell
