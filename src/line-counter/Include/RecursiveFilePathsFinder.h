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

    FilePaths findFilePaths(const Paths&) const override;

private:
    FilePaths findFilePathsInPath(const Path&) const;
    bool pathIsFile(const Path&) const;
    FilePaths getAllFilePathsFromDirectory(const Path&) const;
    Paths getAllPathsFromDirectory(const Path&) const;

    std::shared_ptr<utils::FileAccess> fileAccess;
};
}