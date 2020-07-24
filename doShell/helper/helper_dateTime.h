// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#ifndef DOSHELL_HELPER_HELPER_DATETIME_H_
#define DOSHELL_HELPER_HELPER_DATETIME_H_

#include <regex> // NOLINT [build/c++11]
#include <string>

namespace helper {
namespace DateTime {

static const char FORMAT_ISO_8601[] = "%Y-%m-%dT%H:%M:%SZ";

// @see https://www.oreilly.com/library/view/regular-expressions-cookbook/9781449327453/ch04s07.html
static const char kRegExIso8601DateTime[] =
    R"(^(-?(?:[1-9][0-9]*)?[0-9]{4})-(1[0-2]|0[1-9])-(3[01]|0[1-9]|[12][0-9])T(2[0-3]|[01][0-9]):([0-5][0-9]):([0-5][0-9])Z$)";

std::string GetCurrentDateTimeFormatted(const std::string& format);

std::string GetCurrentDateTimeInIso8601();

extern bool IsIso8601Date(const std::string &str);

}  // namespace DateTime
}  // namespace helper

#endif  // DOSHELL_HELPER_HELPER_DATETIME_H_
