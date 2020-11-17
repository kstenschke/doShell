// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#include <doShell/helper/helper_json.h>

namespace helper {

// (naive but sufficient) JSON detection - object w/ single level of tuple(s)
bool Json::IsJson(const std::string &str) {
  if (str.empty() || str[0] != '{') return false;

  const char *kStr = str.c_str();

  return (helper::String::Contains(kStr, "\"")
          || helper::String::Contains(kStr, "'"))
         && helper::String::Contains(kStr, ":")
         && helper::String::EndsWith(kStr, "}");
}

// find offsets of single and double quote delimiters
// around JSON keys and values
std::vector<int64_t> Json::findJsonItemOffsets(std::string json) {
  std::vector<int64_t> offsets;

  bool prev_was_backslash = false;
  bool is_in_string = false;
  char prev_quote = '"';
  int16_t index = -1;

  for (char c : json) {
    ++index;

    if (prev_was_backslash) {
      prev_was_backslash = c == '\\';
      continue;
    }

    if (c == '\\') {
      prev_was_backslash = true;
      continue;
    }

    if (!is_in_string
        && (c == '"' || c == '\'')) {
      is_in_string = true;
      prev_quote = c;

      offsets.push_back(index);
    } else if (c == prev_quote) {
      is_in_string = false;
      offsets.push_back(index);
    }
  }

  return offsets;
}

void Json::stringReplaceByJsonTuples(std::string *str,
                                              const std::string &json) {
  auto offsets = helper::Json::findJsonItemOffsets(json);

  u_long amount_offsets = offsets.size();

  uint32_t i = 0;

  while (i < amount_offsets) {
    // Extract key/value tuples
    auto offset_start = offsets[i] + 1;
    auto offset_end = offsets[i + 1];

    std::string key = json.substr(offset_start, offset_end - offset_start);

    offset_start = offsets[i + 2] + 1;
    offset_end = offsets[i + 3];

    std::string value = json.substr(offset_start, offset_end - offset_start);

    // Replace
    helper::String::ReplaceAll(str, key, value);

    i+= 4;
  }
}

}  // namespace helper
