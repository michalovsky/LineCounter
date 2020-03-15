#pragma once

#include "FilePathsFinder.h"
#include "utils/FileAccess.h"
#include <memory>

namespace lineCounter
{

class RecursiveFilePathsFinder : public FilePathsFinder
{
public:
    explicit RecursiveFilePathsFinder(std::shared_ptr<utils::FileAccess>);

    FilePaths findFilePaths(const std::string& directoryPath) const override;

private:
    std::vector<std::string> getAllPathsFromDirectory(const std::string& directoryPath) const;

    std::shared_ptr<utils::FileAccess> fileAccess;
};
}