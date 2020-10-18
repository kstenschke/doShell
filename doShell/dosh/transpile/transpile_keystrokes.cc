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
      ->TranspileHitKey("#hitBackspace", "BackSpace", "51")
      ->TranspileHitKey("#hitLeft", "Left", "123")
      ->TranspileHitKey("#hitRight", "Right", "124")
      ->TranspileHitKey("#hitDown", "Down", "125")
      ->TranspileHitKey("#hitUp", "Up", "126")
      ->TranspileHitKey("#hitDelete", "Delete", "51")
      ->TranspileHitKey("#hitEnter", "KP_Enter", "36")
      ->TranspileHitKey("#hitEsc", "Escape", "53")

      ->TranspileHitKey("#hitModUp", "ctrl+Up", "126 using {option down}")
      ->TranspileHitKey("#hitModRight", "ctrl+Right", "124 using {option down}")
      ->TranspileHitKey("#hitModDown", "ctrl+Down", "125 using {option down}")
      ->TranspileHitKey("#hitModLeft", "ctrl+Left", "123 using {option down}")

      ->TranspileHitKey("#hitShiftModUp",
                        "Shift_L+ctrl+Up",
                        "126 using {shift down, option down}")
      ->TranspileHitKey("#hitShiftModRight",
                        "Shift_L+ctrl+Right",
                        "124 using {shift down, option down}")
      ->TranspileHitKey("#hitShiftModDown",
                        "Shift_L+ctrl+Down",
                        "125 using {shift down, option down}")
      ->TranspileHitKey("#hitShiftModLeft",
                        "Shift_L+ctrl+Left",
                        "123 using {shift down, option down}")

      ->TranspileHitFunctionKeys()
      ->TranspileHitTab()

      ->TranspileCopyAll()
      ->TranspileCutAll()

      ->TranspileHitCopy()

      ->TranspileCut()
      ->TranspileHitFind()
      ->TranspilePaste()

      ->TranspileSelectAll();

  delete instance;
}

transpileKeystrokes* transpileKeystrokes::TranspileHitKey(
    const std::string &command,
    const std::string &xdotool_key,
    const std::string &mac_key) {
  if (std::string::npos == code_->find(command)) return this;

#if __linux__
  helper::String::ReplaceAll(code_, command, "xdotool key " + xdotool_key);
#else
  helper::String::ReplaceAll(
      code_,
      command,
      "osascript -e 'tell application \"System Events\" to key code "
          + mac_key + "'");
#endif

  return this;
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

transpileKeystrokes* transpileKeystrokes::TranspileCutAll() {
  helper::String::ReplaceAll(code_, "#copyAll", "#selectAll\n#hitCut");

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
