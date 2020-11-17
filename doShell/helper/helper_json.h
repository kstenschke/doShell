// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#ifndef DOSHELL_HELPER_HELPER_JSON_H_
#define DOSHELL_HELPER_HELPER_JSON_H_

#include <doShell/helper/helper_string.h>

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

namespace helper::Json {

// (naive but sufficient) JSON detection - object w/ single level of tuple(s)
extern bool IsJson(const std::string &str);

// find offsets of single and double quote delimiters
// around JSON keys and values
std::vector<int64_t> findJsonItemOffsets(std::string json);

void stringReplaceByJsonTuples(std::string *str,
                               const std::string &json);

}  // namespace helper::Json

#endif  // DOSHELL_HELPER_HELPER_JSON_H_
