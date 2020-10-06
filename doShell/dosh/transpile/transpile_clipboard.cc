// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#include <doShell/dosh/transpile/transpile_clipboard.h>

namespace doShell {

void transpileClipboard::Transpile(std::string *code) {
  TranspileSetClipboard(code);

  TranspileCopyPaste(code);
  TranspileCopyAll(code);
  TranspileCutAll(code);

  TranspileAppendClipboardToFile(code);
  TranspileSaveClipboardToFile(code);
}

bool transpileClipboard::TranspileSetClipboard(std::string *code) {
  if (std::string::npos == code->find("#setClipboard ")) return false;

  #if __linux__
    std::string replacement = "echo '$1' | xclip -sel clip #";
  #else
    std::string replacement = "osascript -e 'set the clipboard to \"$1\"'";
  #endif

  std::regex exp(R"(#setClipboard \"(.*)\")");
  *code = std::regex_replace(*code, exp, replacement);

  return true;
}

bool transpileClipboard::TranspileAppendClipboardToFile(std::string *code) {
  if (std::string::npos == code->find("#appendClipboardToFile ")) return false;

  std::string replacement =
      "/home/kay/CLionProjects/shellDo/bin/linux/dosh appendClipboardToFile $1";

  std::regex exp(R"(#appendClipboardToFile \"(.*)\")");
  *code = std::regex_replace(*code, exp, replacement);

  return true;
}

bool transpileClipboard::TranspileSaveClipboardToFile(std::string *code) {
  if (std::string::npos == code->find("#saveClipboardToFile ")) return false;

  std::string replacement =
      "/home/kay/CLionProjects/shellDo/bin/linux/dosh saveClipboardToFile $1";

  std::regex exp(R"(#saveClipboardToFile \"(.*)\")");
  *code = std::regex_replace(*code, exp, replacement);

  return true;
}

bool transpileClipboard::TranspileCopyPaste(std::string *code) {
  if (std::string::npos == code->find("#copyPaste ")) return false;

  #if __linux__
    std::string replacement =
      "echo '$1' | xclip -sel clip #\n"
      "xdotool key ctrl+v";
  #else
      std::string replacement =
          "osascript -e 'set the clipboard to \"$1\"'\n"
          "osascript -e 'tell app \"System Events\" to keystroke \"v\" using command down'";
  #endif

  std::regex exp(R"(#copyPaste \"(.*)\")");

  *code = std::regex_replace(*code, exp, replacement);

  return true;
}

bool transpileClipboard::TranspileCopyAll(std::string *code) {
  if (std::string::npos == code->find("#copyAll")) return false;

  return helper::String::ReplaceAll(
      code, "#selectAll\n#hitCopy", "xdotool type ") > 0;
}

bool transpileClipboard::TranspileCutAll(std::string *code) {
  return helper::String::ReplaceAll(code, "#cutAll", "#selectAll\n#hitCut") > 0;
}
}  // namespace doShell
