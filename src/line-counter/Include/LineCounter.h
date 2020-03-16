#pragma once

#include <memory>

#include "FilePathsSelector.h"
#include "utils/FileAccess.h"

namespace lineCounter
{

class LineCounter
{
public:
    LineCounter(std::unique_ptr<FilePathsSelector>, std::shared_ptr<utils::FileAccess>);

    long getAmountOfLines(const ConfigFilePaths&) const;

private:
    FilePaths getAllFilePathsFromPath(const ConfigFilePaths&) const;
    long calculateLinesFromFilePaths(const FilePaths&) const;

    std::vector<std::string> listOfFiles;
    std::unique_ptr<FilePathsSelector> filePathsSelector;
    std::shared_ptr<utils::FileAccess> fileAccess;
};

}
