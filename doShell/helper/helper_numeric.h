// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#ifndef DOSHELL_HELPER_HELPER_NUMERIC_H_
#define DOSHELL_HELPER_HELPER_NUMERIC_H_

#include <cstdio>
#include <cstdint>
#include <string>
#include <cmath>

namespace helper {
namespace Numeric {

bool IsEven(int number);

int GetAmountDigits(int n);

int ExtractLeadingNumber(std::string str);

}  // namespace Numeric
}  // namespace helper

#endif  // DOSHELL_HELPER_HELPER_NUMERIC_H_
