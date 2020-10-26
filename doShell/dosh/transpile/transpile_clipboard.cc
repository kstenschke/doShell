// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#include <doShell/dosh/transpile/transpile_clipboard.h>

namespace doShell {
transpileClipboard::transpileClipboard(std::string *code,
                                       std::string *path_binary) {
  code_ = code;
  path_binary_ = path_binary;
}

void transpileClipboard::Transpile(std::string *code,
                                   std::string *path_binary) {
  auto *instance = new transpileClipboard(code, path_binary);

  instance
      ->TranspileSetClipboard()
      ->TranspileGetClipboard()

      ->TranspileCopyPaste()
      ->TranspileCopyAll()
      ->TranspileCutAll()

      ->TranspilePregMatchAllInClipboard()

      ->TranspileCommand("#extractBetweenFromClipboard ")
      ->TranspileCommand("#replaceAfterFromClipboard ")
      ->TranspileCommand("#replaceAllFromClipboard ")
      ->TranspileCommand("#replaceBeforeFromClipboard ")
      ->TranspileCommand("#replaceBetweenFromClipboard ", 3)
      ->TranspileCommand("#replaceFirstFromClipboard ")
      ->TranspileCommand("#replaceLastFromClipboard ")

      ->TranspileAppendClipboardToFile()
      ->TranspileLoadClipboard()
      ->TranspileSaveClipboard();

  delete instance;
}

transpileClipboard* transpileClipboard::TranspileCommand(
    const std::string &command, int amount_args
) {
  if (!helper::String::Contains(*code_, command)) return this;

  std::regex exp;
  std::string replacement;

  if (amount_args == 2) {
    exp = command + "(.*) (.*)";
    replacement = "$(" + *path_binary_ + " " + command.substr(1) + "$1 $2)";
  } else if (amount_args == 3) {
    exp = command + "(.*) (.*) (.*)";
    replacement = "$(" + *path_binary_ + " " + command.substr(1) + "$1 $2 $3)";
  }

  *code_ = std::regex_replace(*code_, exp, replacement);

  return this;
}

transpileClipboard* transpileClipboard::TranspileSetClipboard() {
  if (std::string::npos == code_->find("#setClipboard ")) return this;

  #if __linux__
    std::string replacement = "echo '$1' | xclip -sel clip #";
  #else
    std::string replacement = "osascript -e 'set the clipboard to \"$1\"'";
  #endif

  if (std::string::npos != code_->find("#setClipboard \"")) {
    std::regex exp(R"(#setClipboard \"([a-zA-Z0-9.\-_:\/?&= ]+)\")");
    *code_ = std::regex_replace(*code_, exp, replacement);
  }

  if (std::string::npos != code_->find("#setClipboard '")) {
    std::regex exp(R"(#setClipboard '([a-zA-Z0-9.\-_:\/?&= ]+)')");
    *code_ = std::regex_replace(*code_, exp, replacement);
  }

  std::regex exp(R"(#setClipboard ([a-zA-Z0-9.\-_:\/?&= ]+))");
  *code_ = std::regex_replace(*code_, exp, replacement);

  return this;
}

transpileClipboard* transpileClipboard::TranspileGetClipboard() {
  if (std::string::npos == code_->find("#getClipboard")) return this;

  helper::String::ReplaceAll(
      code_,
      "#getClipboard",
      "$(" + *path_binary_ + " getClipboard)");

  return this;
}

// TODO(kay): refactor: use single parametric method
//            instead of multiple hard-coded dedicated methods
transpileClipboard* transpileClipboard::TranspileAppendClipboardToFile() {
  if (std::string::npos == code_->find("#appendClipboardToFile ")) return this;

  std::string replacement = *path_binary_ + " appendClipboardToFile $1";

  std::regex exp(R"(#appendClipboardToFile \"(.*)\")");
  *code_ = std::regex_replace(*code_, exp, replacement);

  return this;
}

transpileClipboard* transpileClipboard::TranspileLoadClipboard() {
  if (std::string::npos == code_->find("#loadClipboard ")) return this;

  std::string replacement = *path_binary_ + " loadClipboard $1";

  std::regex exp(R"(#loadClipboard ([a-zA-Z0-9.-_:/?&=]+))");
  *code_ = std::regex_replace(*code_, exp, replacement);

  return this;
}

transpileClipboard* transpileClipboard::TranspileSaveClipboard() {
  if (std::string::npos == code_->find("#saveClipboard ")) return this;

  std::string replacement = *path_binary_ + " saveClipboard $1";

  std::regex exp(R"(#saveClipboard ([a-zA-Z0-9.-_]+))");
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
          "osascript -e 'tell app \"System Events\" "
          "to keystroke \"v\" using command down'\n"
          "sleep 0.1\n";
  #endif

  std::regex exp(R"(#copyPaste \"(.*)\")");

  *code_ = std::regex_replace(*code_, exp, replacement);

  exp = (R"(#copyPaste \'(.*)\')");

  *code_ = std::regex_replace(*code_, exp, replacement);

  return this;
}

transpileClipboard* transpileClipboard::TranspileCopyAll() {
  if (std::string::npos == code_->find("#copyAll")) return this;

  helper::String::ReplaceAll(code_, "#hitSelectAll\n#hitCopy", "xdotool type ");

  return this;
}

transpileClipboard* transpileClipboard::TranspileCutAll() {
  helper::String::ReplaceAll(code_, "#cutAll", "#hitSelectAll\n#hitCut");

  return this;
}

transpileClipboard* transpileClipboard::TranspilePregMatchAllInClipboard() {
  if (std::string::npos == code_->find("#pregMatchAllInClipboard")) return this;

  helper::String::ReplaceAll(
      code_,
      "#pregMatchAllInClipboard",
      *path_binary_ + " pregMatchAllInClipboard");

  return this;
}
}  // namespace doShell
