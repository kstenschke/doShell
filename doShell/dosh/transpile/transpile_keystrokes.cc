// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#include <doShell/dosh/transpile/transpile_keystrokes.h>

namespace doShell {

transpileKeystrokes::transpileKeystrokes(std::string *code) {
  code_ = code;
}

void transpileKeystrokes::Transpile(std::string *code) {
  auto *instance = new transpileKeystrokes(code);

  instance
    ->TranspileType()
    ->TranspileHitBackspace()
    ->TranspileHitDelete()
    ->TranspileHitEnter()
    ->TranspileHitEsc()
    ->TranspileHitFunctionKeys()
    ->TranspileHitTab()

    ->TranspileCopyAll()
    ->TranspileHitCopy()

    ->TranspileCut()
    ->TranspileHitFind()
    ->TranspilePaste()

    ->TranspileSelectAll();

  delete instance;
}

transpileKeystrokes* transpileKeystrokes::TranspileHitCopy() {
  if (std::string::npos == code_->find("#hitCopy")) return this;

  #if __linux__
    helper::String::ReplaceAll(code_, "#hitCopy", "xdotool key ctrl+c\nsleep 0.1");
  #else
    helper::String::ReplaceAll(
        code_,
        "#hitCopy",
        "osascript -e 'tell application \"System Events\" to keystroke \"c\" "
        "using command down'\nsleep 0.1");
  #endif

  return this;
}

transpileKeystrokes* transpileKeystrokes::TranspileHitFind() {
  if (std::string::npos == code_->find("#hitFind")) return this;

  #if __linux__
    helper::String::ReplaceAll(code_, "#hitFind", "xdotool key ctrl+f");
  #else
    helper::String::ReplaceAll(
      code_,
      "#hitFind",
      "osascript -e 'tell application \"System Events\" to keystroke \"f\" "
      "using command down'");
  #endif

  return this;
}

transpileKeystrokes* transpileKeystrokes::TranspileCut() {
  #if __linux__
    helper::String::ReplaceAll(code_, "#cut", "xdotool key ctrl+x");
  #else
    helper::String::ReplaceAll(
      code_,
      "#cut",
      "osascript -e 'tell application \"System Events\" to keystroke \"x\" "
      "using command down'");
  #endif

  return this;
}

transpileKeystrokes* transpileKeystrokes::TranspileCopyAll() {
  helper::String::ReplaceAll(code_, "#copyAll", "#selectAll\n#hitCopy");

  return this;
}

transpileKeystrokes* transpileKeystrokes::TranspilePaste() {
  #if __linux__
    helper::String::ReplaceAll(code_, "#paste", "xdotool key ctrl+v");
  #else
    helper::String::ReplaceAll(
      code_,
      "#paste",
      "osascript -e 'tell application \"System Events\" to keystroke \"v\" "
      "using command down'");
  #endif

  return this;
}

transpileKeystrokes* transpileKeystrokes::TranspileSelectAll() {
  if (std::string::npos == code_->find("#selectAll")) return this;

  #if __linux__
    helper::String::ReplaceAll(
     code_,
     "#selectAll",
     "xdotool key ctrl+a\n
     sleep 0.1");
  #else
    helper::String::ReplaceAll(
      code_,
      "#selectAll",
      "osascript -e 'tell application \"System Events\" to keystroke \"a\" "
      "using command down'\n"
      "sleep 0.1");
  #endif

  return this;
}

transpileKeystrokes* transpileKeystrokes::TranspileHitEnter() {
  if (std::string::npos == code_->find("#hitEnter")) return this;

  #if __linux__
    helper::String::ReplaceAll(code_, "#hitEnter", "xdotool key KP_Enter");
  #else
    helper::String::ReplaceAll(
        code_,
        "#hitEnter",
        "osascript -e 'tell application \"System Events\" to key code 36'");
  #endif

  return this;
}

transpileKeystrokes* transpileKeystrokes::TranspileHitBackspace() {
  if (std::string::npos == code_->find("#hitBackspace")) return this;

  #if __linux__
    helper::String::ReplaceAll(code_, "#hitBackspace", "xdotool key BackSpace");
  #else
    helper::String::ReplaceAll(
      code_,
      "#hitBackspace",
      "osascript -e 'tell application \"System Events\" to key code 51'");
  #endif

  return this;
}

transpileKeystrokes* transpileKeystrokes::TranspileHitDelete() {
  if (std::string::npos == code_->find("#hitDelete")) return this;

  #if __linux__
    return helper::String::ReplaceAll(
      code_, "#hitDelete", "xdotool key Delete") > 0;
  #else
    helper::String::ReplaceAll(
      code_,
      "#hitDelete",
      "osascript -e 'tell application \"System Events\" to key code 51'");
  #endif

  return this;
}

transpileKeystrokes* transpileKeystrokes::TranspileHitTab() {
  if (std::string::npos == code_->find("#hitTab")) return this;

  #if __linux__
    helper::String::ReplaceAll(code_, "#hitTab", "xdotool key Tab");
  #else
    helper::String::ReplaceAll(
      code_,
      "#hitTab",
      "osascript -e 'tell application \"System Events\" "
      "to keystroke (ASCII character 9)'");
  #endif

  return this;
}

transpileKeystrokes* transpileKeystrokes::TranspileHitEsc() {
  if (std::string::npos == code_->find("#hitEsc")) return this;

  #if __linux__
    helper::String::ReplaceAll(
        code_,
        "#hitEsc",
        "xdotool key Escape");
  #else
    helper::String::ReplaceAll(
      code_,
      "#hitEsc",
      "osascript -e 'tell application \"System Events\" to key code 53'");
  #endif

  return this;
}

transpileKeystrokes* transpileKeystrokes::TranspileHitFunctionKeys() {
  if (std::string::npos == code_->find("#hitF")) return this;

  #if __linux__
    std::string replacement = "xdotool key F$1";

    std::regex exp(R"(#hitF(\d+))");
    *code_ = std::regex_replace(*code_, exp, replacement);
  #else
  // TODO(kay): add applescript
  #endif

  return this;
}

transpileKeystrokes* transpileKeystrokes::TranspileType() {
  #if __linux__
    helper::String::ReplaceAll(code_, "#type", "xdotool type ");
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

  return this;
}
}  // namespace doShell
