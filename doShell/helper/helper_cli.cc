// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#include <doShell/helper/helper_cli.h>
#include <zconf.h>

namespace helper {

std::string Cli::GetSelfPath() {
  char buff[1024];

  ssize_t len = ::readlink("/proc/self/exe", buff, sizeof(buff) - 1);

  if (len != -1) {
    buff[len] = '\0';
    return std::string(buff);
  }

  // TODO(kay): handle error condition
  return "";
}

void Cli::Execute(const char *command) {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
  system(command);
#pragma clang diagnostic pop
}

std::string Cli::GetExecutionResponse(const char *command) {
  FILE *fp;
  char path[1035];

  // Open the command for reading
  fp = popen(command, "r");
  if (fp ==nullptr) return "Failed to run command";

  // Read the output a line at a time
  std::string result;
  while (fgets(path, sizeof(path), fp) !=nullptr) {
    result += path;
  }

  pclose(fp);

  return result;
}

}  // namespace helper
