// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#ifndef DOSHELL_HELPER_HELPER_FILE_H_
#define DOSHELL_HELPER_HELPER_FILE_H_

//#include <doShell/app/app_log.h>

#include <dirent.h>
#include <sys/stat.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#ifdef __linux__
#include <unistd.h>
#include <algorithm>
#include <chrono>  // NOLINT [build/c++11]
#endif

#include <doShell/helper/helper_string.h>

namespace helper {
namespace File {

extern bool IsDir(const std::string& path);

// Check whether given file exists
extern bool FileExists(const std::string &path_file);

// Resolve path: keep absolute or make relative from given (binary) path
extern bool ResolvePath(const std::string &pwd,
                        std::string *path,
                        bool must_exist = false);

// Get trailing name component of given path, e.g. the filename w/ extension
extern std::string GetBasename(const std::string &path);

extern std::streampos GetFileSize(std::ifstream &file);

extern bool GetFileContents(
    const std::string &path_file, std::string *contents);

extern std::string GetFileContents(std::ifstream &file);

extern u_int32_t GetLongestLineLength(const std::string &path_file_1,
                                      const std::string &path_file_2 = "",
                                      bool ensure_files_exist = false);

extern bool WriteToNewFile(const std::string &path_file,
                           const std::string &content);

extern int AppendToFile(const std::string &filename,
                        const std::string &content);

extern bool CopyFile(const std::string &path_source,
                     const std::string &path_destination);

extern bool Remove(const char *path);

extern bool RemoveRecursive(const char *file_path);

extern std::string GetLastPathSegment(std::string path);

extern std::vector<std::string> ScanDir(const char *path);

extern std::vector<std::string> ScanDirRecursive(
    const char *path,
    std::vector<std::string> files,
    const std::string& remove_prefix = "");

extern std::string GlobPatternToRegEx(const std::string &pattern);

extern std::string GetTmpName();

extern bool IsWordCompatibleImage(const std::string &filename);

}  // namespace File
}  // namespace helper

#endif  // DOSHELL_HELPER_HELPER_FILE_H_
