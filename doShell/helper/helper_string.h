// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#ifndef DOSHELL_HELPER_HELPER_STRING_H_
#define DOSHELL_HELPER_HELPER_STRING_H_

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

namespace helper::String {

extern bool IsJson(const std::string &str);

extern bool IsWhiteSpaceOrEmpty(const std::string &str);

// line is not empty, not commented and no shebang line?
extern bool IsExecutableBashLine(const std::string &str);

// Check whether given string ends w/ given string
bool EndsWith(std::string const &str, std::string const &ending);

// Check whether given string starts w/ given prefix
extern bool StartsWith(const char *str, const char *prefix);
extern bool StartsWith(const std::string *str, const char *prefix);
extern bool StartsWith(const std::string *str, const std::string *prefix);

extern bool StartsNumeric(const char *str);

extern bool Contains(const std::string &haystack, const char *needle);
extern bool Contains(const std::string &haystack, const std::string& needle);

extern int SubStrCount(const std::string &haystack,
                       const std::string& needle,
                       size_t offset = 0);

int FindLast(const std::string &str,
             const std::string &needle,
             int32_t offset_start,
             int32_t offset_end);

extern bool Replace(std::string *haystack,
                    const char *needle,
                    const char *replacement);

extern int ReplaceAll(std::string *haystack,
                      const std::string &needle,
                      const std::string &replacement = "");

extern int ReplaceFirst(std::string *haystack,
                        const std::string &needle,
                        const std::string &replacement);

extern int ReplaceLast(std::string *haystack,
                        const std::string &needle,
                        const std::string &replacement);

// Replace text including and between LHS and RHS
std::string ReplaceBetween(const std::string &str,
                           const std::string &lhs,
                           const std::string &rhs,
                           const std::string &replacement = "");

// Get substring between given surrounding left- and center-hand-side delimiters
extern std::string GetSubStrBetween(const std::string &str,
                                    const char *lhs,
                                    const char *rhs,
                                    u_int32_t *offset);

extern std::string GetSubStrAfter(const std::string &str,
                                  const char *lhs,
                                  u_int32_t *offset = 0);

extern std::string GetSubStrBetween(const std::string &str,
                                    const char *lhs,
                                    const char *rhs);

// Split given string by given character delimiter into vector of strings
extern std::vector<std::string> Explode(std::string const &str, char delimiter);

extern std::string RenderTwoColumns(
    const std::string& col_1, const std::string& col_2, int amount_gap = 4);

extern void LTrim(std::string *s);
extern void RTrim(std::string *s);
extern void Trim(std::string *s);

extern std::string ToLower(std::string str);
extern std::string ToUpper(const std::string &str);

extern u_int32_t GetMaxLength(const std::vector<std::string>& str_1);

extern std::string Repeat(const std::string& str, u_int16_t amount);
}  // namespace helper::String

#endif  // DOSHELL_HELPER_HELPER_STRING_H_
