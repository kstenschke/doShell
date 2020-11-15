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

      ->TranspilePasteRenderedFromFile()
      ->TranspilePregMatchAllInClipboard()

      ->TranspileCommand("_extractBetweenFromClipboard ")
      ->TranspileCommand("_replaceAfterFromClipboard ")
      ->TranspileCommand("_replaceAllFromClipboard ")
      ->TranspileCommand("_replaceBeforeFromClipboard ")
      ->TranspileCommand("_replaceBetweenFromClipboard ", 3)
      ->TranspileCommand("_replaceFirstFromClipboard ")
      ->TranspileCommand("_replaceLastFromClipboard ")

      ->TranspileAppendClipboardToFile()
      ->TranspileLoadIntoClipboard()
      ->TranspileLoadIntoClipboard();

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
  if (std::string::npos == code_->find("_setClipboard ")) return this;

  auto offset_start = code_->find("_setClipboard");
  auto offset_newline = code_->find("\n", offset_start);

  std::string arguments =
      code_->substr(offset_start + 13, offset_newline - (offset_start + 13));

  *code_ =
      code_->substr(0, offset_start)
          + *path_binary_ + " setClipboard" + arguments
          + code_->substr(offset_newline);

  return this;
}

transpileClipboard* transpileClipboard::TranspileGetClipboard() {
  if (std::string::npos == code_->find("_getClipboard")) return this;

  helper::String::ReplaceAll(
      code_,
      "_getClipboard",
      "$(" + *path_binary_ + " getClipboard)");

  return this;
}

// TODO(kay): refactor: use single parametric method
//            instead of multiple hard-coded dedicated methods
transpileClipboard* transpileClipboard::TranspileAppendClipboardToFile() {
  if (std::string::npos == code_->find("_appendClipboardToFile ")) return this;

  std::string replacement = *path_binary_ + " appendClipboardToFile $1";

  std::regex exp(R"(_appendClipboardToFile \"(.*)\")");
  *code_ = std::regex_replace(*code_, exp, replacement);

  return this;
}

transpileClipboard* transpileClipboard::TranspileLoadIntoClipboard() {
  if (std::string::npos == code_->find("_loadIntoClipboard ")) return this;

  std::string replacement = *path_binary_ + " loadIntoClipboard $1";

  std::regex exp(R"(_loadIntoClipboard ([a-zA-Z0-9.-_:/?&=]+))");
  *code_ = std::regex_replace(*code_, exp, replacement);

  return this;
}

transpileClipboard* transpileClipboard::TranspileSaveClipboard() {
  if (std::string::npos == code_->find("_saveClipboard ")) return this;

  std::string replacement = *path_binary_ + " saveClipboard $1";

  std::regex exp(R"(_saveClipboard ([a-zA-Z0-9.-_]+))");
  *code_ = std::regex_replace(*code_, exp, replacement);

  return this;
}

transpileClipboard* transpileClipboard::TranspileCopyPaste() {
  if (std::string::npos == code_->find("_copyPaste ")) return this;

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

  std::regex exp(R"(_copyPaste \"(.*)\")");

  *code_ = std::regex_replace(*code_, exp, replacement);

  exp = (R"(_copyPaste \'(.*)\')");

  *code_ = std::regex_replace(*code_, exp, replacement);

  return this;
}

transpileClipboard* transpileClipboard::TranspileCopyAll() {
  if (std::string::npos == code_->find("_copyAll")) return this;

  helper::String::ReplaceAll(code_, "_hitSelectAll\n_hitCopy", "xdotool type ");

  return this;
}

transpileClipboard* transpileClipboard::TranspileCutAll() {
  helper::String::ReplaceAll(code_, "_cutAll", "_hitSelectAll\n_hitCut");

  return this;
}

transpileClipboard* transpileClipboard::TranspilePasteRenderedFromFile() {
  if (std::string::npos == code_->find("_pasteRenderedFromFile ")) return this;

  std::string replacement =
      *path_binary_ + " pasteRenderedFromFile $1\n"
      "sleep 0.1\n"
      "_hitPaste\n";

  std::regex exp(R"(_pasteRenderedFromFile (.+?)(?=\n))");
  *code_ = std::regex_replace(*code_, exp, replacement);

  return this;
}

transpileClipboard* transpileClipboard::TranspilePregMatchAllInClipboard() {
  if (std::string::npos == code_->find("_pregMatchAllInClipboard")) return this;

  helper::String::ReplaceAll(
      code_,
      "_pregMatchAllInClipboard",
      *path_binary_ + " pregMatchAllInClipboard");

  return this;
}
}  // namespace doShell
