// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#ifndef DOSHELL_DOSH_RUNTIMEOPTIONS_RUNTIMEOPTIONS_H_
#define DOSHELL_DOSH_RUNTIMEOPTIONS_RUNTIMEOPTIONS_H_

#include <doShell/app/app_argument.h>
#include <doShell/app/app_command.h>
#include <doShell/app/app_help.h>
#include <doShell/config.h>
#include <doShell/dosh/transpile/transpileClipboard.h>
#include <doShell/dosh/transpile/transpileBrowser.h>
#include <doShell/dosh/transpile/transpileKeystrokes.h>
#include <doShell/helper/helper_cli.h>

#include <cstring>
#include <iostream>
#include <string>
#include <thread>  // NOLINT
#include <vector>

namespace doShell {

class runtimeOptions {
 public:
  static bool ReplaceRunTimeMacros(std::string *code, bool is_linux);
};

}  // namespace doShell

#endif  // DOSHELL_DOSH_RUNTIMEOPTIONS_RUNTIMEOPTIONS_H_
