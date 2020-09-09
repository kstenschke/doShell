// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#include <doShell/dosh/transpile/transpile_keystrokes.h>

namespace doShell {
void transpileKeystrokes::Transpile(std::string *code, bool is_linux) {
  TranspileType(code, is_linux);
  TranspileHitBackspace(code, is_linux);
  TranspileHitDelete(code, is_linux);
  TranspileHitEnter(code, is_linux);
  TranspileHitEsc(code, is_linux);
  TranspileHitFunctionKeys(code, is_linux);
  TranspileHitTab(code, is_linux);

  TranspileHitCopy(code, is_linux);
  TranspileCut(code, is_linux);
  TranspileHitFind(code, is_linux);
  TranspilePaste(code, is_linux);

  TranspileSelectAll(code, is_linux);
}

bool transpileKeystrokes::TranspileHitCopy(std::string *code, bool is_linux) {
  if (std::string::npos == code->find("#hitCopy")) return false;

  return helper::String::ReplaceAll(
      code,
      "#hitCopy",
      is_linux
      ? "xdotool key ctrl+c"
      : "osascript -e 'tell application \"System Events\" to keystroke \"c\" "
        "using command down'") > 0;
}

bool transpileKeystrokes::TranspileHitFind(std::string *code, bool is_linux) {
  if (std::string::npos == code->find("#hitFind")) return false;

  return helper::String::ReplaceAll(
      code,
      "#hitFind",
      is_linux
      ? "xdotool key ctrl+f"
      : "osascript -e 'tell application \"System Events\" to keystroke \"f\" "
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
  if (std::string::npos == code->find("#selectAll")) return false;

  return helper::String::ReplaceAll(
      code,
      "#selectAll",
      is_linux
      ? "xdotool key ctrl+a"
      : "osascript -e 'tell application \"System Events\" to keystroke \"a\" "
        "using command down'") > 0;
}

bool transpileKeystrokes::TranspileHitEnter(std::string *code, bool is_linux) {
  if (std::string::npos == code->find("#hitEnter")) return false;

  bool replaced = helper::String::ReplaceAll(
      code,
      "#hitEnter",
      is_linux
      ? "xdotool key KP_Enter"
      : "osascript -e 'tell application \"System Events\" "
        "to key code 36'") > 0;

  return replaced;
}

bool transpileKeystrokes::TranspileHitBackspace(std::string *code,
                                                bool is_linux) {
  if (std::string::npos == code->find("#hitBackspace")) return false;

  bool replaced = helper::String::ReplaceAll(
      code,
      "#hitBackspace",
      is_linux
      ? "xdotool key BackSpace"
      : "osascript -e 'tell application \"System Events\" "
        "to key code 51'") > 0;

  return replaced;
}

bool transpileKeystrokes::TranspileHitDelete(std::string *code,
                                             bool is_linux) {
  if (std::string::npos == code->find("#hitDelete")) return false;

  bool replaced = helper::String::ReplaceAll(
      code,
      "#hitDelete",
      is_linux
      ? "xdotool key Delete"
      : "osascript -e 'tell application \"System Events\" "
        "to key code 51'") > 0;

  return replaced;
}

bool transpileKeystrokes::TranspileHitTab(std::string *code,
                                                bool is_linux) {
  if (std::string::npos == code->find("#hitTab")) return false;

  bool replaced = helper::String::ReplaceAll(
      code,
      "#hitTab",
      is_linux
      ? "xdotool key Tab"
      : "osascript -e 'tell application \"System Events\" "
        "to keystroke (ASCII character 9)'") > 0;

  return replaced;
}

bool transpileKeystrokes::TranspileHitEsc(std::string *code,
                                          bool is_linux) {
  if (std::string::npos == code->find("#hitEsc")) return false;

  bool replaced = helper::String::ReplaceAll(
      code,
      "#hitEsc",
      is_linux
      ? "xdotool key Escape"
      : "osascript -e 'tell application \"System Events\" "
        "to key code 53'") > 0;

  return replaced;
}

bool transpileKeystrokes::TranspileHitFunctionKeys(std::string *code,
                                          bool is_linux) {
  if (std::string::npos == code->find("#hitF")) return false;

  if (is_linux) {
    std::string replacement = "xdotool key F$1";

    std::regex exp(R"(#hitF(\d+))");
    *code = std::regex_replace(*code, exp, replacement);
  }

  // TODO(kay): add applescript

  return true;
}

bool transpileKeystrokes::TranspileType(std::string *code, bool is_linux) {
  if (is_linux)
    return helper::String::ReplaceAll(
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
