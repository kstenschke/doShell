// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#include <doShell/helper/helper_string.h>

#include <iostream>
#include <regex>  // NOLINT [build/c++11]
#include <utility>

namespace helper {

bool String::IsJson(const std::string &str) {
  if (str.empty() || str[0] != '{') return false;

  const char *kStr = str.c_str();

  return helper::String::Contains(kStr, "\"")
         && helper::String::Contains(kStr, ":")
         && helper::String::EndsWith(kStr, "}");
}

// Check whether given string starts w/ given prefix
bool String::StartsWith(const char *str, const char *prefix) {
  return 0 == strncmp(str, prefix, strlen(prefix));
}

bool String::StartsWith(const std::string *str, const char *prefix) {
  return str->substr(0, strlen(prefix)) == prefix;
}

bool String::StartsWith(const std::string *str, const std::string *prefix) {
  return str->find(*prefix) == 0;
}

// Check whether given string ends w/ given string
bool String::EndsWith(std::string const &str, std::string const &ending) {
  return ending.empty()
      || (ending.size() <= str.size()
          && std::equal(ending.rbegin(), ending.rend(), str.rbegin()));
}

bool String::Contains(const std::string &haystack, const char *needle) {
  return std::string::npos != haystack.find(needle);
}

bool String::Contains(const std::string &haystack, const std::string& needle) {
  return std::string::npos != haystack.find(needle);
}

int String::SubStrCount(const std::string &haystack,
                        const std::string& needle,
                        size_t offset) {
  auto len_needle = needle.length();
  int occurrences = 0;

  while ((offset = haystack.find(needle, offset)) != std::string::npos) {
    ++occurrences;
    offset += len_needle;
  }

  return occurrences;
}

int String::FindLast(const std::string &str,
                     const std::string &needle,
                     int32_t offset_start,
                     int32_t offset_end) {
  auto offset_needle = offset_start;
  auto offset_needle_prev = offset_needle;

  do {
    offset_needle_prev = offset_needle;
    offset_needle = str.find(needle, offset_needle + 1);
  } while (offset_needle != std::string::npos
      && offset_needle < offset_end);

  return
      offset_needle == std::string::npos
          || offset_needle > offset_end
      ? offset_needle_prev
      : offset_needle;
}

bool String::Replace(
    std::string *haystack, const char *needle, const char *replacement) {
  size_t needle_len = strlen(needle);

  size_t index = 0;
  index = (*haystack).find(needle, index);

  if (std::string::npos == index) return false;

  (*haystack).replace(index, needle_len, replacement);

  return true;
}

int String::ReplaceAll(std::string *haystack,
                       const std::string &needle,
                       const std::string &replacement) {
  // Get first occurrence
  size_t pos = (*haystack).find(needle);

  int amount_replaced = 0;

  // Repeat till end is reached
  while (pos != std::string::npos) {
    // Replace this occurrence of sub string
    (*haystack).replace(pos, needle.size(), replacement);

    // Get the next occurrence from the current position
    pos = (*haystack).find(needle, pos + replacement.size());

    amount_replaced++;
  }

  return amount_replaced;
}

int String::ReplaceFirst(std::string *haystack,
                         const std::string &needle,
                         const std::string &replacement) {
  // Get first occurrence
  size_t pos = (*haystack).find(needle);

  if (pos == std::string::npos) return 0;

  // Replace occurrence of sub String
  (*haystack).replace(pos, needle.size(), replacement);

  return 1;
}

int String::ReplaceLast(std::string *haystack,
                         const std::string &needle,
                         const std::string &replacement) {
  // Get last occurrence
  size_t pos = std::string::npos;
  size_t pos_prev;

  do {
    pos_prev = pos;
    pos = (*haystack).find(needle, pos + 1);
  } while (pos != std::string::npos);

  if (pos_prev != std::string::npos) pos = pos_prev;

  if (pos == std::string::npos) return 0;

  // Replace occurrence of sub String
  (*haystack).replace(pos, needle.size(), replacement);

  return 1;
}

// Replace text including and between LHS and RHS
std::string String::ReplaceBetween(const std::string &str,
                                   const std::string &lhs,
                                   const std::string &rhs,
                                   const std::string &replacement) {
  auto offsetStart = str.find(lhs);

  if (std::string::npos == offsetStart) return str;

  size_t offsetEnd = str.find(rhs, offsetStart);

  if (std::string::npos == offsetEnd) return str;

  std::string res = str;
  res.replace(offsetStart, offsetEnd - offsetStart, replacement);

  return res;
}

std::string String::GetSubStrBetween(const std::string &str,
                                     const char *lhs,
                                     const char *rhs,
                                     u_int32_t *offset) {
  size_t offsetStart = str.find(lhs, *offset);

  if (std::string::npos == offsetStart) return "";

  size_t offsetEnd = str.find(rhs, offsetStart);

  if (std::string::npos == offsetEnd) return "";

  // Exclude LHS
  offsetStart += strlen(lhs);

  *offset = offsetStart;

  return str.substr(offsetStart, offsetEnd - offsetStart);
}

std::string String::GetSubStrAfter(const std::string &str,
                                   const char *lhs,
                                   u_int32_t *offset) {
  size_t offsetStart = str.find(lhs, *offset);

  if (std::string::npos == offsetStart) return "";

  // Exclude LHS
  offsetStart += strlen(lhs);

  *offset = offsetStart;

  return str.substr(offsetStart);
}

std::string String::GetSubStrBetween(const std::string &str,
                                     const char *lhs,
                                     const char *rhs) {
  u_int32_t offset = 0;

  return GetSubStrBetween(str, lhs, rhs, &offset);
}

// Split given string by given character delimiter into vector of strings
std::vector<std::string> String::Explode(std::string const &str,
                                         char delimiter) {
  std::vector<std::string> result;
  std::istringstream iss(str);

  for (std::string token; std::getline(iss, token, delimiter);)
    result.push_back(std::move(token));

  return result;
}

std::string String::RenderTwoColumns(
    const std::string& col_1, const std::string& col_2, int amount_gap) {
  std::vector<std::string> lines_1 = Explode(col_1, '\n');
  std::vector<std::string> lines_2 = Explode(col_2, '\n');

  std::string gap = Repeat(" ", amount_gap);

  int len_longest_line = GetMaxLength(lines_1);

  std::string out;

  int amount_lines_2 = lines_2.size();

  int index = 0;

  for (const auto& line : lines_1) {
    out += line;

    uint16_t len_line_1 = line.length();

    if (len_line_1 < len_longest_line)
      out += Repeat(" ", len_longest_line - len_line_1);

    out += gap;

    if (index < amount_lines_2
        && !lines_2[index].empty()) out.append(lines_2[index]);

    out += "\n";

    ++index;
  }

  return out;
}

// Trim from start (in place)
void String::LTrim(std::string *s) {
  (*s).erase(
      (*s).begin(),
      std::find_if(
          (*s).begin(),
          (*s).end(),
          std::not1(std::ptr_fun<int, int>(std::isspace))));
}

// Trim from end (in place)
void String::RTrim(std::string *s) {
  (*s).erase(
      std::find_if(
          (*s).rbegin(),
          (*s).rend(),
          std::not1(std::ptr_fun<int, int>(std::isspace)))
          .base(),
      (*s).end());
}

// Trim from both ends (in place)
void String::Trim(std::string *s) {
  LTrim(s);
  RTrim(s);
}

std::string String::ToLower(std::string str) {
  std::transform(
      str.begin(),
      str.end(),
      str.begin(),
      [](unsigned char c) {
        return std::tolower(c);
      });

  return str;
}

std::string String::ToUpper(const std::string& str) {
  std::string upper;

  for (auto c : str) upper += toupper(c);

  return upper;
}

u_int32_t String::GetMaxLength(const std::vector<std::string>& strings) {
  u_int32_t max = 0;

  for (const auto& str : strings) {
    u_int32_t len = str.length();

    if (len > max) max = len;
  }

  return max;
}

std::string String::Repeat(const std::string& str, u_int16_t amount) {
  std::string out;

  for (u_int16_t i = 0; i < amount; i++) {
    out+= str;
  }

  return out;
}

std::string String::HtmlToText(std::string html) {
  helper::String::ReplaceAll(&html, "\t", " ");

  std::string text;
  bool is_in_tag = false;
  bool is_closing_tag = false;
  bool is_in_child_of_noscript_tag = false;
  char prev_ch;

  std::string current_tag;

  for (char ch : html) {
    if (!is_in_tag && ch == '<') {
      is_in_tag = true;
      current_tag = "";

      if (!text.empty()) {
        prev_ch = text[text.length() - 1];

        if (prev_ch != ' ' && prev_ch != '\n')
        text += ' ';
      }

      continue;
    }

    if (is_in_tag) {
      if (ch == '/' && current_tag.empty()) {
        is_closing_tag = true;

        continue;
      }

      if (ch == '>') {
        is_in_tag = false;

        current_tag = helper::String::Explode(current_tag, ' ')[0];

        if (is_closing_tag) {
          is_closing_tag = false;

          if (current_tag == "noscript") {
            is_in_child_of_noscript_tag = false;
          } else if (text.length() > 0) {
              if (current_tag == "span") {
                text += "\n";
              } else if (current_tag == "title") {
                text += "\n\n";
              }
          }
        } else if (current_tag == "noscript") {
          is_in_child_of_noscript_tag = true;
        }

        continue;
      }

      current_tag += ch;
    }

    if (!is_in_tag) {
      if (is_in_child_of_noscript_tag
          || current_tag == "link"
          || current_tag == "meta"
          || current_tag == "script") continue;

      prev_ch = text[text.length() - 1];

      if (ch == ' '
          && (prev_ch == ' ' || prev_ch == '\n')) continue;

      text += ch;
    }
  }

  return text;
}

}  // namespace helper
