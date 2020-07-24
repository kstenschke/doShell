// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#include <doShell/app/app_log.h>

namespace doShell {

AppLog* AppLog::m_pThis_ = nullptr;

const char AppLog::FORMAT_TIMESTAMP[] = "%Y-%m-%d %H:%M:%S";

AppLog::AppLog() {
  InitMode();

  if (mode_ != LogTo_StdOut && mode_ != LogTo_None) InitLogFile();
}

void AppLog::InitMode() {
  auto env_var = std::getenv("docxBox_verbose");
  verbose_ = env_var != nullptr && 0 == strcmp(env_var, "1");

  env_var = std::getenv("docxBox_notify");

  std::string option = env_var == nullptr
                       ? ""
                       : std::string(env_var);

  if (option.empty() || option == "stdout") {
    return;
  }

  if (option == "log") {
    mode_ = LogMode::LogTo_File;
  } else if (option == "both") {
    mode_ = LogMode::LogTo_FileAndStdOut;
  } else if (option == "off") {
    mode_ = LogMode::LogTo_None;
  }
}

void AppLog::InitLogFile() {
  auto env_var = std::getenv("docxBox_log_path");

  std::string setting_path = env_var == nullptr
                             ? ""
                             : std::string(env_var);

  path_log_file_ = setting_path.empty()
                   ? std::string(std::getenv("PWD")) + "/out.log"
                   : setting_path;

  env_var = std::getenv("docxBox_clear_log_on_start");

  if (env_var != nullptr) {
    std::string setting_flush_on_start = std::string(env_var);
    clear_log_initially_ = setting_flush_on_start == "1";
  }

  bool has_logfile = true;

  if (clear_log_initially_ || !helper::File::FileExists(path_log_file_)) {
    if (!helper::File::WriteToNewFile(path_log_file_, "")) {
      has_logfile = false;
      std::cerr << "Failed create logfile: " << path_log_file_;
    }
  }

  if (verbose_ && has_logfile) {
    std::cout << "Log file is: " << path_log_file_ << "\n";
  }
}

AppLog* AppLog::GetInstance() {
  if (m_pThis_ == nullptr) m_pThis_ = new AppLog();

  return m_pThis_;
}

void AppLog::DeleteInstance() {
  delete m_pThis_;
}

// Store given message for later output to stdout / logout
void AppLog::Notify(const std::string& message,
                    NotificationType type,
                    bool file_only) {
  if (mode_ == LogTo_None) return;

  file_only_messages_.push_back(verbose_ || file_only);

  if (mode_ == LogTo_File || mode_ == LogTo_FileAndStdOut) PushBackTime();

  std::string type_str;

  if (type == NotificationType::Notification_Error)
    type_str = "Error";
  else
    type_str = type == NotificationType::Notification_Warning
               ? "Warning"
               : "Info";

  messages_.push_back("docxBox " + type_str + " - " + message);
}

// Store given error message for later output to stdout / logout
bool AppLog::NotifyError(const std::string& message, bool file_only) {
  GetInstance()->Notify(
      message, NotificationType::Notification_Error, file_only);

  return false;
}

// Warning (= non fatal error, output also non-verbosely)
bool AppLog::NotifyWarning(const std::string& message, bool file_only) {
  GetInstance()->Notify(
      message, NotificationType::Notification_Warning, file_only);

  return true;
}

// Store given informational message for later output to stdout / logout
bool AppLog::NotifyInfo(const std::string& message, bool file_only) {
  GetInstance()->Notify(
      message, NotificationType::Notification_Info, file_only);

  return true;
}

// Log docxBox execution arguments to log file
void AppLog::LogStartUp(const std::vector<std::string>& arguments) {
  std::string arg_values;

  for (const auto& argument : arguments) arg_values += argument + " ";

  NotifyInfo("docxBox executing w/ arguments: " + arg_values, true);
}

// Remember current dateTime (notification occurred)
void AppLog::PushBackTime() {
  timestamps_.push_back(
      helper::DateTime::GetCurrentDateTimeFormatted(FORMAT_TIMESTAMP));
}

void AppLog::Output(bool delete_instance) {
  auto kInstance = GetInstance();

  if (kInstance->mode_ != LogTo_None) {
    if (kInstance->mode_ == LogMode::LogTo_StdOut
        || kInstance->mode_ == LogMode::LogTo_FileAndStdOut)
      kInstance->OutputToStdOut();

    if (kInstance->mode_ == LogMode::LogTo_FileAndStdOut
        || kInstance->mode_ == LogMode::LogTo_File)
      kInstance->OutputToLogFile();
  }

  if (delete_instance) DeleteInstance();
}

void AppLog::OutputToStdOut() {
  std::string prev_message;

  unsigned int index = 0;

  for (auto &message : messages_) {
    if (message == prev_message
        || (!verbose_ && file_only_messages_.at(index))) {
      ++index;

      continue;
    }

    if (verbose_ || MessageTypeExtortsOutput(message)) {
      std::cerr << message + "\n";

      prev_message = message;
    }

    ++index;
  }
}

bool AppLog::MessageTypeExtortsOutput(const std::string &message) {
  // [E]rror and [W]arning: Output to stdout
  return message[8] == 'E' || message[8] == 'W';
}

void AppLog::OutputToLogFile() {
  std::string out;
  std::string prev_message;

  unsigned int index = 0;

  for (auto &message : messages_) {
    if (message == prev_message) {
      ++index;

      continue;
    }

    out += timestamps_.at(index) + " - " + message.substr(8) + "\n";

    prev_message = message;

    ++index;
  }

  if (!clear_log_initially_) out = "\n" + out;

  helper::File::AppendToFile(path_log_file_, out);
}

bool AppLog::IsSilent() {
  AppLog *kInstance = GetInstance();

  return kInstance->mode_ != LogTo_StdOut
      && kInstance->mode_ != LogTo_FileAndStdOut;
}

}  // namespace doShell
