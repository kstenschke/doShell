// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#ifndef DOSHELL_APP_APP_ARGUMENT_H_
#define DOSHELL_APP_APP_ARGUMENT_H_

#include <doShell/app/app_log.h>
#include <doShell/helper/helper_string.h>
#include <doShell/helper/helper_file.h>

#include <cstring>
#include <string>
#include <vector>

namespace doShell {

class AppArgument {
 public:
  AppArgument(int argc, std::vector<std::string>  argv);

  static std::string ResolvePathFromArgument(
      const std::string &pwd,
      int argc,
      const std::vector<std::string> &argv,
      int index_argument,
      bool must_exist = true);

 private:
  int argc_;
  std::vector<std::string> argv_;
};

}  // namespace doShell

#endif  // DOSHELL_APP_APP_ARGUMENT_H_
