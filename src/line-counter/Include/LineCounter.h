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

    long getAmountOfLines(const std::string& dirPath) const;

private:
    long calculateLines(const std::string& dirPath) const;
    std::vector<std::string> getFilePathsFromDirectory(const std::string& dirPath) const;

    std::vector<std::string> listOfFiles;
    std::unique_ptr<FilePathsSelector> filePathsSelector;
    std::shared_ptr<utils::FileAccess> fileAccess;
};

}
