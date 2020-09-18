// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#ifndef DOSHELL_DOSH_RUNTIME_H_
#define DOSHELL_DOSH_RUNTIME_H_

#include <doShell/app/app_command.h>
#include <doShell/app/app_help.h>
#include <doShell/app/app_log.h>
#include <doShell/config.h>
#include <doShell/dosh/transpile/transpile_browser.h>
#include <doShell/dosh/transpile/transpile_clipboard.h>
#include <doShell/dosh/transpile/transpile_dialog.h>
#include <doShell/dosh/transpile/transpile_keystrokes.h>
#include <doShell/dosh/transpile/transpile_macro.h>
#include <doShell/dosh/transpile/transpile_platform.h>
#include <doShell/dosh/transpile/transpile_random.h>
#include <doShell/dosh/transpile/transpile_string.h>
#include <doShell/dosh/transpile/transpile_terminal.h>
#include <doShell/dosh/transpile/transpile_url.h>
#include <doShell/helper/helper_cli.h>
#include <doShell/helper/helper_file.h>

#include <cstring>
#include <iostream>
#include <string>
#include <thread>  // NOLINT
#include <vector>

namespace doShell {

class S2sTranspiler {
 public:
  // Constructor: init (resolve) command and arguments
  S2sTranspiler(int argc, const std::vector<std::string>& argv);

  // Transpile given *.do.sh file to *.sh
  bool Compile(bool overwrite_intermediary_file = false);

  // 1. Transpile given *.do.sh file to *.sh,
  // 2. Create temporary dosh copy of *.sh w/ dosh macros replaced
  // 3. Execute dosh copy
  // 4. Delete dosh copy
  bool Execute();

  virtual ~S2sTranspiler();

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

  static int ReplaceLineNumberMacros(std::string *code);

  void InitPathSourceDirectory();
  void InitPathFileCompiled();
  void InitPathPhtml();
  void InitPathFileRuntime();

  static bool RemoveSheBangLine(std::string *import_content);

  void TranspileCommands();
  bool SourceContainsCommands();

  bool ParsePhp();

  void CleanupSource();
  void MakeRuntimeScriptExecutable() const;
  void SaveSourceToRuntimeScript();
  bool RemoveTemporaryExecutionFile();
  std::string GetBasePathBySourceFile() const;
};

}  // namespace doShell

#endif  // DOSHELL_DOSH_RUNTIME_H_
