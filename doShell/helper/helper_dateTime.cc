// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#include <doShell/helper/helper_dateTime.h>

namespace helper {

std::string DateTime::GetTimestamp() {
  return "12345678";
}

// Get string of current timestamp, w/ given offset in days added,
// in given format.
std::string DateTime::GetCurrentDateTimeFormatted(const std::string& format) {
  time_t raw_time;
  struct tm *time_info;
  char buffer[80];

  time(&raw_time);
  time_info = localtime(&raw_time);  // NOLINT [build/c++11]

  strftime(buffer, sizeof(buffer), format.c_str(), time_info);
  std::string str(buffer);

  return str;
}

// @return dateTime in ISO 8601 format, e.g. "1994-11-05T13:15:30Z"
// @see ISO-8601 https://www.w3.org/TR/NOTE-datetime
std::string DateTime::GetCurrentDateTimeInIso8601() {
  return GetCurrentDateTimeFormatted(FORMAT_ISO_8601);
}

// Verify given string being ISO8601 date. Ex: 2016-02-22T10:31:00Z
bool DateTime::IsIso8601Date(const std::string &str) {
  if (str.empty()) return false;

  std::regex pattern(kRegExIso8601DateTime);

  return std::regex_match (str, pattern);
}

}  // namespace helper
