// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#ifndef DOSHELL_COMPILER_COMPILER_H_
#define DOSHELL_COMPILER_COMPILER_H_

#include <doShell/app/app_argument.h>
#include <doShell/app/app_command.h>
#include <doShell/app/app_help.h>
#include <doShell/config.h>

#include <cstring>
#include <iostream>
#include <string>
#include <vector>

namespace doShell {

class Compiler {
 public:
  // Constructor: init (resolve) command and arguments
  Compiler(int argc, const std::vector<std::string>& argv);

  // Transpile given *.do.sh file to *.sh
  bool Compile();

  // 1. Transpile given *.do.sh file to *.sh,
  // 2. Create temporary runtime copy of *.sh w/ runtime macros replaced
  // 3. Execute runtime copy
  // 4. Delete runtime copy
  bool Execute();

  virtual ~Compiler();

 private:
  int argc_;
  std::vector<std::string> argv_;

  std::string path_source_file_abs_;
  std::string path_compiled_file_abs_;
  std::string path_runtime_file_abs_;
  std::string path_source_directory_abs_;

  std::string source_;

  bool CompileAllInPath();

  bool LoadSource();

  bool ResolveImports();

  void InitPathSourceDirectory();
  void InitPathFileCompiled();
  void InitPathFileRuntime();

  bool ReplaceRunTimeMacrosInSource();

  static bool RemoveSheBangLine(std::string *import_content);

  void CleanupSource();
  void MakeRuntimeScriptExecutable() const;
  void SaveSourceToRuntimeScript();
};

}  // namespace doShell

#endif  // DOSHELL_COMPILER_COMPILER_H_
