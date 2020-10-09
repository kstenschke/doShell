// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#include <doShell/dosh/transpile/transpile_clipboard.h>

namespace doShell {
transpileClipboard::transpileClipboard(std::string *code) {
  code_ = code;
}

void transpileClipboard::Transpile(std::string *code) {
  auto *instance = new transpileClipboard(code);

  instance
    ->TranspileSetClipboard()

    ->TranspileCopyPaste()
    ->TranspileCopyAll()
    ->TranspileCutAll()

    ->TranspileAppendClipboardToFile()
    ->TranspileSaveClipboardToFile();

  delete instance;
}

transpileClipboard* transpileClipboard::TranspileSetClipboard() {
  if (std::string::npos == code_->find("#setClipboard ")) return this;

  #if __linux__
    std::string replacement = "echo '$1' | xclip -sel clip #";
  #else
    std::string replacement = "osascript -e 'set the clipboard to \"$1\"'";
  #endif

  std::regex exp(R"(#setClipboard \"(.*)\")");
  *code_ = std::regex_replace(*code_, exp, replacement);

  return this;
}

transpileClipboard* transpileClipboard::TranspileAppendClipboardToFile() {
  if (std::string::npos == code_->find("#appendClipboardToFile ")) return this;

  std::string replacement =
      "/home/kay/CLionProjects/shellDo/bin/linux/dosh appendClipboardToFile $1";

  std::regex exp(R"(#appendClipboardToFile \"(.*)\")");
  *code_ = std::regex_replace(*code_, exp, replacement);

  return this;
}

transpileClipboard* transpileClipboard::TranspileSaveClipboardToFile() {
  if (std::string::npos == code_->find("#saveClipboardToFile ")) return this;

  std::string replacement =
      "/home/kay/CLionProjects/shellDo/bin/linux/dosh saveClipboardToFile $1";

  std::regex exp(R"(#saveClipboardToFile \"(.*)\")");
  *code_ = std::regex_replace(*code_, exp, replacement);

  return this;
}

transpileClipboard* transpileClipboard::TranspileCopyPaste() {
  if (std::string::npos == code_->find("#copyPaste ")) return this;

  #if __linux__
    std::string replacement =
      "echo '$1' | xclip -sel clip #\n"
      "xdotool key ctrl+v";
  #else
      std::string replacement =
          "osascript -e 'set the clipboard to \"$1\"'\n"
          "sleep 0.1\n"
          "osascript -e 'tell app \"System Events\" to keystroke \"v\" using command down'\n"
          "sleep 0.1\n";
  #endif

  std::regex exp(R"(#copyPaste \"(.*)\")");

  *code_ = std::regex_replace(*code_, exp, replacement);

  return this;
}

transpileClipboard* transpileClipboard::TranspileCopyAll() {
  if (std::string::npos == code_->find("#copyAll")) return this;

  helper::String::ReplaceAll(code_, "#selectAll\n#hitCopy", "xdotool type ");

  return this;
}

transpileClipboard* transpileClipboard::TranspileCutAll() {
  helper::String::ReplaceAll(code_, "#cutAll", "#selectAll\n#hitCut");

  return this;
}
}  // namespace doShell
