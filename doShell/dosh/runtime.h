// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#ifndef DOSHELL_DOSH_RUNTIME_H_
#define DOSHELL_DOSH_RUNTIME_H_

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
#include <thread>
#include <vector>

namespace doShell {

class Compiler {
 public:
  // Constructor: init (resolve) command and arguments
  Compiler(int argc, const std::vector<std::string>& argv);

  // Transpile given *.do.sh file to *.sh
  bool Compile();

  // 1. Transpile given *.do.sh file to *.sh,
  // 2. Create temporary dosh copy of *.sh w/ dosh macros replaced
  // 3. Execute dosh copy
  // 4. Delete dosh copy
  bool Execute();

  virtual ~Compiler();

 private:
  int argc_;
  std::vector<std::string> argv_;

#ifdef __linux__
  bool is_linux_ = true;
#else
  bool is_linux_ = false;
#endif

  std::string path_source_file_abs_;
  std::string path_compiled_file_abs_;
  std::string path_phtml_file_abs_;
  std::string path_runtime_file_abs_;
  std::string path_source_directory_abs_;

  std::string source_;

  bool CompileAllInPath();

  bool LoadSource();

  bool ResolveImports();

  void InitPathSourceDirectory();
  void InitPathFileCompiled();
  void InitPathPhtml();
  void InitPathFileRuntime();

  bool ReplaceRunTimeMacrosInSource();

  static bool RemoveSheBangLine(std::string *import_content);

  void TranspileCommands();
  bool ContainsCommands();

  bool ParsePhp();

  void CleanupSource();
  void MakeRuntimeScriptExecutable() const;
  void SaveSourceToRuntimeScript();
};

}  // namespace doShell

#endif  // DOSHELL_DOSH_RUNTIME_H_
