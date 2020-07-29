// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#ifndef DOSHELL_HELPER_HELPER_STRING_H_
#define DOSHELL_HELPER_HELPER_STRING_H_

#include <doShell/helper/helper_numeric.h>

#include <fcntl.h>

#include <algorithm>
#include <codecvt>
#include <cstring>
#include <cmath>
#include <functional>
#include <locale>
#include <regex>  // NOLINT [build/c++11]
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace helper {
namespace String {

std::string UnwrapQuotes(const std::string& str);

// Check whether given string ends w/ given string
bool EndsWith(std::string const &str, std::string const &ending);

bool EndsWithCaseInsensitive(const char *str, const std::string &ending);
bool EndsWithCaseInsensitive(std::string str, const std::string &ending);

// Check whether given string starts w/ given prefix
extern bool StartsWith(const char *str, const char *prefix);
extern bool StartsWith(const std::string *str, const char *prefix);
extern bool StartsWith(const std::string *str, const std::string *prefix);

extern bool StartsNumeric(const char *str);

extern bool IsAnyOf(const std::string& str, std::vector<std::string> endings);

bool Matches(const std::string &subject, const std::string &pattern);

extern bool Contains(const std::string &haystack, const char *needle);
extern bool Contains(const std::string &haystack, const std::string& needle);

extern int SubStrCount(const std::string &haystack,
                       const std::string& needle,
                       size_t offset = 0);

extern int64_t FindNthOccurrence(const std::string &haystack,
                                 const std::string& needle,
                                 int n,
                                 size_t offset = 0);

int FindLast(const std::string &str,
             const std::string &needle,
             unsigned long offset_start,
             unsigned long offset_end);

extern bool IsWhiteSpace(const std::string &str);

extern void Remove(std::string *haystack, const std::regex &pattern);

extern int RemoveAll(std::string *haystack, const std::string& needle);

extern bool Replace(std::string *haystack,
                    const char *needle,
                    const char *replacement);

extern int ReplaceAll(std::string *haystack,
                      const std::string &needle,
                      const std::string &replacement);

// Get substring between given surrounding left- and center-hand-side delimiters
extern std::string GetSubStrBetween(const std::string &str,
                                    const char *lhs,
                                    const char *rhs,
                                    u_int32_t *offset);

extern std::string GetSubStrBetween(const std::string &str,
                                    const char *lhs,
                                    const char *rhs);

extern int OffsetChar(const std::string &str, char c, int offset = 0);

// Split given string by given character delimiter into vector of strings
extern std::vector<std::string> Explode(std::string const &str, char delimiter);

extern std::string GetTrailingWord(std::string *str);

extern std::string ExtractTrailingNumber(
    std::string str, std::string default_if_none = "1");

extern std::string ExtractLeadingNumber(std::string str);

extern std::string Implode(
    std::vector<std::string> strings, const char* delimiter = ", ");

extern std::string RenderTwoColumns(
    const std::string& col_1, const std::string& col_2, int amount_gap = 4);

extern void LTrim(std::string *s);
extern void RTrim(std::string *s);
extern void Trim(std::string *s);

extern bool IsNumeric(
    std::string *str,
    bool trim = false,
    bool can_contain_punctuation = false,
    bool can_contain_spaces = false);

extern bool IsAllUpper(const std::string& str);

extern std::string ToLower(std::string str);
extern std::string ToUpper(const std::string &str);

extern u_int32_t GetMaxLength(const std::vector<std::string>& str_1);

extern u_int32_t GetMaxLineLength(const std::vector<std::string>& str_1,
                                  const std::vector<std::string>& str_2);

extern std::string Repeat(const std::string& str, u_int16_t amount);

extern std::string GetRandomNumericString(
    u_int32_t length,
    bool starts_with_zero = false);

}  // namespace String
}  // namespace helper

#endif  // DOSHELL_HELPER_HELPER_STRING_H_
