#pragma once

#include <memory>

#include "FilePathsFinder.h"
#include "utils/FileAccess.h"

namespace lineCounter
{

class RecursiveFilePathsFinder : public FilePathsFinder
{
public:
    explicit RecursiveFilePathsFinder(std::shared_ptr<utils::FileAccess>);

    FilePaths findFilePaths(const std::string& path) const override;

private:
    bool pathIsFile(const std::string& path) const;
    FilePaths getAllPathsFromDirectory(const std::string& directoryPath) const;

    std::shared_ptr<utils::FileAccess> fileAccess;
};
}