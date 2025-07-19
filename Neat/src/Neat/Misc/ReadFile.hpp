#pragma once

#include <fstream>
#include <filesystem>
#include <expected>
#include <vector>
#include <string>
#include <iostream>

namespace Neat {
constexpr std::uintmax_t kMaxAssetFileSize = 100 * 1024 * 1024;  // 100 MB

enum class FileErrorCode {
  FileNotFound,
  PermissionDenied,
  NotAFile,
  ReadFailure,
  FileTooLarge,
  Unknown
};

struct FileError {
  FileErrorCode code;
  std::filesystem::path path;
  std::string message;
};

std::ostream& operator<<(std::ostream& os, const FileError& err);
std::expected<std::string, FileError> readFile(
    const std::filesystem::path& path);
}  // namespace Neat