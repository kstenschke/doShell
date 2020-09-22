// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#ifndef DOSHELL_DOSH_RUNTIME_OPTION_RUNTIME_OPTION_H_
#define DOSHELL_DOSH_RUNTIME_OPTION_RUNTIME_OPTION_H_

#include <doShell/app/app_command.h>
#include <doShell/app/app_help.h>
#include <doShell/config.h>
#include <doShell/dosh/transpile/transpile_clipboard.h>
#include <doShell/dosh/transpile/transpile_browser.h>
#include <doShell/dosh/transpile/transpile_keystrokes.h>
#include <doShell/helper/helper_cli.h>

#include <cstring>
#include <iostream>
#include <string>
#include <thread>  // NOLINT
#include <vector>

namespace doShell {

class transpileMacros {
 public:
  static void Transpile(std::string *code);
};

}  // namespace doShell

#endif  // DOSHELL_DOSH_RUNTIME_OPTION_RUNTIME_OPTION_H_
