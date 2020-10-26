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
      ->TranspileHitKey("#hitBackspace", "BackSpace", " code 51")
      ->TranspileHitKey("#hitHome", "Home", " code 115")
      ->TranspileHitKey("#hitEnd", "End", " code 119")
      ->TranspileHitKey("#hitPageDown", "Page_Down", " code 121")
      ->TranspileHitKey("#hitPageUp", "Page_Up", " code 116")

      ->TranspileHitKey("#hitLeft", "Left", " code 123")
      ->TranspileHitKey("#hitRight", "Right", " code 124")
      ->TranspileHitKey("#hitDown", "Down", " code 125")
      ->TranspileHitKey("#hitUp", "Up", " code 126")

      ->TranspileHitKey("#hitDelete", "Delete", " code 51")
      ->TranspileHitKey("#hitEnter", "KP_Enter", " code 36")
      ->TranspileHitKey("#hitEsc", "Escape", " code 53")

      ->TranspileHitKey("#hitModUp",
                        "ctrl+Up",
                        " code 126 using {option down}")

      ->TranspileHitKey("#hitModRight",
                        "ctrl+Right",
                        " code 124 using {option down}")

      ->TranspileHitKey("#hitModDown",
                        "ctrl+Down",
                        " code 125 using {option down}")

      ->TranspileHitKey("#hitModLeft",
                        "ctrl+Left",
                        " code 123 using {option down}")

      ->TranspileHitKey("#hitShiftModUp",
                        "Shift_L+ctrl+Up",
                        " code 126 using {shift down, option down}")

      ->TranspileHitKey("#hitShiftModRight",
                        "Shift_L+ctrl+Right",
                        " code 124 using {shift down, option down}")

      ->TranspileHitKey("#hitShiftModDown",
                        "Shift_L+ctrl+Down",
                        " code 125 using {shift down, option down}")

      ->TranspileHitKey("#hitShiftModLeft",
                        "Shift_L+ctrl+Left",
                        " code 123 using {shift down, option down}")

      ->TranspileHitFunctionKeys()

      ->TranspileHitKey("#hitTab", "Tab", "stroke (ASCII character 9)")

      ->TranspileHitCopyAll()
      ->TranspileHitCutAll()

      ->TranspileHitKey("#hitCut",
                        "ctrl+x",
                        "stroke \"x\" using command down",
                        "0.1")

      ->TranspileHitKey("#hitCopy",
                        "ctrl+c",
                        "stroke \"c\" using command down",
                        "0.1")

      ->TranspileHitKey("#hitFind",
                        "ctrl+f",
                        "stroke \"f\" using command down")

      ->TranspileHitKey("#hitPaste",
                        "ctrl+v",
                        "stroke \"v\" using command down",
                        "0.1")

      ->TranspileHitKey("#hitSelectAll",
                        "ctrl+a",
                        "stroke \"a\" using command down",
                        "0.1")

      ->TranspileHitKey("#moveCaretToLineEnd",
                        "End",
                        " code 124 using {command down}",
                        "0.1")

      ->TranspileHitKey("#moveCaretToLineStart",
                        "Home",
                        " code 123 using {command down}",
                        "0.1");

  delete instance;
}

transpileKeystrokes* transpileKeystrokes::TranspileHitKey(
    const std::string &command,
    const std::string &xdotool_key,
    const std::string &mac_key,
    const std::string &sleep) {
  if (std::string::npos == code_->find(command)) return this;

#if __linux__
  helper::String::ReplaceAll(
    code_,
    command,
    "xdotool key " + xdotool_key
    + (sleep.empty() ? "" : "\nsleep " + sleep));
#else
  helper::String::ReplaceAll(
      code_,
      command,
      "osascript -e 'tell application \"System Events\" to key"
          + mac_key + "'"
          + (sleep.empty() ? "" : "\nsleep " + sleep));
#endif

  return this;
}

transpileKeystrokes* transpileKeystrokes::TranspileHitCopyAll() {
  helper::String::ReplaceAll(code_, "#copyAll", "#hitSelectAll\n#hitCopy");

  return this;
}

transpileKeystrokes* transpileKeystrokes::TranspileHitCutAll() {
  helper::String::ReplaceAll(code_,
                             "#cutAll",
                             "#hitSelectAll\nsleep 0.1\n#hitCut");

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
