// Copyright (c) 2020 Kay Stenschke
// Licensed under the MIT License - https://opensource.org/licenses/MIT

#include <doShell/helper/helper_file.h>
#include <doShell/app/app_log.h>

namespace helper {

bool File::IsDir(const std::string& path) {
  struct stat buffer;

  stat(path.c_str(), &buffer);

  return S_ISDIR(buffer.st_mode);
}

bool File::FileExists(const std::string &path_file) {
  return access(path_file.c_str(), F_OK) != -1;
}

bool File::GetFileContents(const std::string &path_file,
                           std::string *contents) {
  if (!FileExists(path_file))
    return doShell::AppLog::NotifyError("File not found: "  + path_file);

  std::ifstream file(path_file);

  *contents = GetFileContents(file);

  return true;
}

std::string File::GetFileContents(std::ifstream &file) {
  std::streampos length = GetFileSize(file);

  // Read whole file into the buffer
  std::vector<char> buffer(static_cast<u_int32_t>(length));
  file.read(&buffer[0], length);

  std::string str(buffer.begin(), buffer.end());

  file.close();

  return str;
}

u_int32_t File::GetLongestLineLength(const std::string &path_file_1,
                                     const std::string &path_file_2,
                                     bool ensure_files_exist) {
  u_int32_t len_1 = 0;

  if (!ensure_files_exist || FileExists(path_file_1)) {
    std::string contents;
    GetFileContents(path_file_1, &contents);

    std::vector<std::string> lines = helper::String::Explode(contents, '\n');

    len_1 = helper::String::GetMaxLength(lines);
  }

  if (!path_file_2.empty()
      && (!ensure_files_exist || FileExists(path_file_2))) {
    std::string contents;
    GetFileContents(path_file_2, &contents);

    std::vector<std::string> lines = helper::String::Explode(contents, '\n');

    auto len_2 = helper::String::GetMaxLength(lines);

    if (len_2 > len_1) return len_2;
  }

  return len_1;
}

// Resolve path: keep absolute or make relative from given (binary) path
bool File::ResolvePath(const std::string &pwd,
                       std::string *path,
                       bool must_exist) {
  helper::String::Trim(path);

  if (!helper::String::StartsWith(path, "/"))
    *path = helper::String::EndsWith(pwd, "/")
            ? pwd + (*path)
            : pwd + "/" + (*path);

  return must_exist
             && (helper::File::IsDir(*path)
                 || !helper::File::FileExists(*path))
         ? doShell::AppLog::NotifyError(std::string("File not found: ") + *path)
         : true;
}

// Get trailing name component of given path, e.g. the filename w/ extension
std::string File::GetBasename(const std::string &path) {
  return GetLastPathSegment(path);
}

std::streampos File::GetFileSize(std::ifstream &file) {
  file.seekg(0, std::ios::end);
  std::streampos length = file.tellg();
  file.seekg(0, std::ios::beg);

  return length;
}

bool File::WriteToNewFile(const std::string &path_file,
                          const std::string &content) {
  if (FileExists(path_file)) Remove(path_file.c_str());

  std::ofstream outfile(path_file);

  if (!content.empty()) outfile << content;

  outfile.close();

  return FileExists(path_file);
}

int File::AppendToFile(const std::string &filename,
                       const std::string &content) {
  std::ofstream out_file;
  out_file.open(filename, std::ios_base::app);
  out_file << content;

  out_file.close();

  return 0;
}

bool File::CopyFile(const std::string &path_source,
                    const std::string &path_destination) {
  if (!FileExists(path_source))
    return doShell::AppLog::NotifyError(
        "Copy file failed - file not found: " + path_source);

  std::ifstream source(path_source, std::ios::binary);
  std::ofstream destination(path_destination, std::ios::binary);

  destination << source.rdbuf();

  source.close();
  destination.close();

  return true;
}

bool File::Remove(const char *path) {
  return remove(path) == 0;
}

bool File::RemoveRecursive(const char *path) {
  if (!IsDir(path)) return Remove(path);

  DIR *d = opendir(path);
  size_t path_len = strlen(path);

  int result = -1;

  if (d) {
    struct dirent *p;

    result = 0;
    while (!result && (p=readdir(d))) {
      int r2 = -1;
      char *buffer;
      size_t len;

      if (!strcmp(p->d_name, ".") || !strcmp(p->d_name, ".."))
        continue;

      len = path_len + strlen(p->d_name) + 2;
      buffer = static_cast<char *>(malloc(len));

      if (buffer) {
        struct stat stat_buffer{};

        snprintf(buffer, len, "%s/%s", path, p->d_name);

        if (!stat(buffer, &stat_buffer)) {
          if (S_ISDIR(stat_buffer.st_mode))
            r2 = RemoveRecursive(buffer);
          else
            r2 = unlink(buffer);
        }

        free(buffer);
      }

      result = r2;
    }

    closedir(d);
  }

  if (!result) result = rmdir(path);

  return result;
}

std::string File::GetLastPathSegment(std::string path) {
  if (helper::String::Contains(path, "/")) {
    std::vector<std::string> parts = helper::String::Explode(path, '/');

    return parts[parts.size() - 1];
  }

  return path;
}

std::vector<std::string> File::ScanDir(const char *path) {
  struct dirent **namelist;
  int filecount;

  std::vector<std::string> files;

  filecount = scandir(path, &namelist, nullptr, alphasort);

  if (filecount > 0) {
    for (int i = 0; i < filecount; i++) {
      std::string path_file;

      if (namelist[i]->d_name[0] != '.') {
        path_file += path;
        path_file  += "/";
        path_file  += namelist[i]->d_name;

        files.push_back(path_file);
      }
    }

    while (filecount--) {
      free(namelist[filecount]);
    }

    free(namelist);
  }

  return files;
}

std::vector<std::string> File::ScanDirRecursive(
    const char *path,
    std::vector<std::string> files,
    const std::string& remove_prefix
) {
  struct dirent **namelist;
  int filecount;

  bool do_remove_prefix = !remove_prefix.empty();

  filecount = scandir(path, &namelist, nullptr, alphasort);

  if (filecount > 0) {
    for (int i = 0; i < filecount; i++) {
      std::string path_file;

      if (namelist[i]->d_name[0] != '.') {
        path_file += path;
        path_file  += "/";
        path_file  += namelist[i]->d_name;

        if (IsDir(path_file)) {
          files = helper::File::ScanDirRecursive(
              path_file.c_str(),
              files,
              remove_prefix);
        } else {
          if (do_remove_prefix)
            helper::String::Replace(&path_file, remove_prefix.c_str(), "");

          files.push_back(path_file);
        }
      }
    }

    while (filecount--) {
      free(namelist[filecount]);
    }

    free(namelist);
  }

  return files;
}

std::string File::GlobPatternToRegEx(const std::string &pattern) {
  if (pattern.empty() || pattern == "*") return std::string(pattern);

  std::string reg_ex = pattern;

  // Escape reg-ex control characters that aren't globbing control characters
  helper::String::ReplaceAll(&reg_ex, "\\", "\\\\");
  helper::String::ReplaceAll(&reg_ex, ".", "\\.");
  helper::String::ReplaceAll(&reg_ex, "(", "\\(");
  helper::String::ReplaceAll(&reg_ex, ")", "\\)");
  helper::String::ReplaceAll(&reg_ex, "[", "\\[");
  helper::String::ReplaceAll(&reg_ex, "]", "\\]");
  helper::String::ReplaceAll(&reg_ex, "{", "\\{");
  helper::String::ReplaceAll(&reg_ex, "}", "\\}");

  // Convert globbing- to regex control characters
  helper::String::ReplaceAll(&reg_ex, "*", ".*");
  helper::String::ReplaceAll(&reg_ex, "?", ".");

  return reg_ex;
}

std::string File::GetTmpName() {
  char *buffer;
  size_t max_len;

  int timestamp = static_cast<int>(time(nullptr));

  max_len = snprintf(nullptr, 0, "%d", timestamp);
  buffer = reinterpret_cast<char *>(malloc(max_len + 1));
  snprintf(buffer, max_len+1, "%d", timestamp);

  auto tmp_name = std::string(buffer);

  free(buffer);

  return tmp_name;
}

bool File::IsWordCompatibleImage(const std::string &filename) {
  auto str = helper::String::ToLower(filename);

  return (helper::String::EndsWith(str, ".bmp")
      || helper::String::EndsWith(str, ".emg")
      || helper::String::EndsWith(str, ".gif")
      || helper::String::EndsWith(str, ".jpeg")
      || helper::String::EndsWith(str, ".jpg")
      || helper::String::EndsWith(str, ".png")
      || helper::String::EndsWith(str, ".tif")
      || helper::String::EndsWith(str, ".tiff")
      || helper::String::EndsWith(str, ".wmf"));
}

}  // namespace helper
