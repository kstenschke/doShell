// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#include <doShell/dosh/transpile/transpile_keystrokes.h>

namespace doShell {
void transpileKeystrokes::Transpile(std::string *code) {
  TranspileType(code);
  TranspileHitBackspace(code);
  TranspileHitDelete(code);
  TranspileHitEnter(code);
  TranspileHitEsc(code);
  TranspileHitFunctionKeys(code);
  TranspileHitTab(code);

  TranspileHitCopy(code);
  TranspileCut(code);
  TranspileHitFind(code);
  TranspilePaste(code);

  TranspileSelectAll(code);
}

bool transpileKeystrokes::TranspileHitCopy(std::string *code) {
  if (std::string::npos == code->find("#hitCopy")) return false;

  #if __linux__
    return helper::String::ReplaceAll(code, "#hitCopy", "xdotool key ctrl+c") > 0
  #else
    return helper::String::ReplaceAll(
        code,
        "#hitCopy",
        "osascript -e 'tell application \"System Events\" to keystroke \"c\" "
        "using command down'") > 0;
  #endif
}

bool transpileKeystrokes::TranspileHitFind(std::string *code) {
  if (std::string::npos == code->find("#hitFind")) return false;

  #if __linux__
    return helper::String::ReplaceAll(
      code,
      "#hitFind",
      "xdotool key ctrl+f") > 0;
  #else
    return helper::String::ReplaceAll(
      code,
      "#hitFind",
      "osascript -e 'tell application \"System Events\" to keystroke \"f\" "
      "using command down'") > 0;
  #endif
}

bool transpileKeystrokes::TranspileCut(std::string *code) {
  #if __linux__
    return helper::String::ReplaceAll(
      code, "#cut", "xdotool key ctrl+x") > 0;
  #else
    return helper::String::ReplaceAll(
      code,
      "#cut",
      "osascript -e 'tell application \"System Events\" to keystroke \"x\" "
      "using command down'") > 0;
  #endif
}

bool transpileKeystrokes::TranspilePaste(std::string *code) {
  #if __linux__
    return helper::String::ReplaceAll(
      code, "#paste", "xdotool key ctrl+v") > 0;
  #else
    return helper::String::ReplaceAll(
      code,
      "#paste",
      "osascript -e 'tell application \"System Events\" to keystroke \"v\" "
      "using command down'") > 0;
  #endif
}

bool transpileKeystrokes::TranspileSelectAll(std::string *code) {
  if (std::string::npos == code->find("#selectAll")) return false;

  #if __linux__
    return helper::String::ReplaceAll(
      code, "#selectAll", "xdotool key ctrl+a") > 0;
  #else
    return helper::String::ReplaceAll(
      code,
      "#selectAll",
      "osascript -e 'tell application \"System Events\" to keystroke \"a\" "
      "using command down'") > 0;
  #endif
}

bool transpileKeystrokes::TranspileHitEnter(std::string *code) {
  if (std::string::npos == code->find("#hitEnter")) return false;

  #if __linux__
    return helper::String::ReplaceAll(
      code, "#hitEnter", "xdotool key KP_Enter") > 0;
  #else
    return helper::String::ReplaceAll(
        code,
        "#hitEnter",
        "osascript -e 'tell application \"System Events\" to key code 36'") > 0;
  #endif
}

bool transpileKeystrokes::TranspileHitBackspace(std::string *code) {
  if (std::string::npos == code->find("#hitBackspace")) return false;

  #if __linux__
    return helper::String::ReplaceAll(
      code, "#hitBackspace", "xdotool key BackSpace") > 0;
  #else
    return helper::String::ReplaceAll(
      code,
      "#hitBackspace",
      "osascript -e 'tell application \"System Events\" to key code 51'") > 0;
  #endif
}

bool transpileKeystrokes::TranspileHitDelete(std::string *code) {
  if (std::string::npos == code->find("#hitDelete")) return false;

  #if __linux__
    return helper::String::ReplaceAll(
      code, "#hitDelete", "xdotool key Delete") > 0;
  #else
    return helper::String::ReplaceAll(
      code,
      "#hitDelete",
      "osascript -e 'tell application \"System Events\" to key code 51'") > 0;
  #endif
}

bool transpileKeystrokes::TranspileHitTab(std::string *code) {
  if (std::string::npos == code->find("#hitTab")) return false;

  #if __linux__
    return helper::String::ReplaceAll(
      code,
      "#hitTab",
      "xdotool key Tab") > 0;
  #else
    return helper::String::ReplaceAll(
      code,
      "#hitTab",
      "osascript -e 'tell application \"System Events\" "
      "to keystroke (ASCII character 9)'") > 0;
  #endif
}

bool transpileKeystrokes::TranspileHitEsc(std::string *code) {
  if (std::string::npos == code->find("#hitEsc")) return false;

  #if __linux__
    return helper::String::ReplaceAll(
        code,
        "#hitEsc",
        "xdotool key Escape") > 0;
  #else
    return helper::String::ReplaceAll(
      code,
      "#hitEsc",
      "osascript -e 'tell application \"System Events\" to key code 53'") > 0;
  #endif
}

bool transpileKeystrokes::TranspileHitFunctionKeys(std::string *code) {
  if (std::string::npos == code->find("#hitF")) return false;

  #if __linux__
    std::string replacement = "xdotool key F$1";

    std::regex exp(R"(#hitF(\d+))");
    *code = std::regex_replace(*code, exp, replacement);
  #else
  // TODO(kay): add applescript
  #endif

  return true;
}

bool transpileKeystrokes::TranspileType(std::string *code) {
  #if __linux__
    return helper::String::ReplaceAll(
        code, "#type", "xdotool type ") > 0;
  #else
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
  #endif

  return false;
}
}  // namespace doShell
