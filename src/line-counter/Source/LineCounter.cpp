#include "LineCounter.h"

#include "utils/StringHelper.h"

namespace lineCounter
{
LineCounter::LineCounter(std::unique_ptr<FilePathsSelector> filePathsSelectorInit,
                         std::shared_ptr<utils::FileAccess> fileAccessInit)
    : filePathsSelector{std::move(filePathsSelectorInit)}, fileAccess{std::move(fileAccessInit)}
{
}

long LineCounter::getAmountOfLines(const ConfigFilePaths& paths) const
{
    const auto filePaths = getAllFilePathsFromPath(paths);
    return calculateLinesFromFilePaths(filePaths);
}

FilePaths LineCounter::getAllFilePathsFromPath(const ConfigFilePaths& paths) const
{
    return filePathsSelector->selectFilePaths(paths);
}

long LineCounter::calculateLinesFromFilePaths(const FilePaths& filePaths) const
{
    long amountOfLinesFromFiles = 0;

    for (const auto& filePath : filePaths)
    {
        const auto fileContent = fileAccess->readContent(filePath);
        if (not fileContent.empty())
        {
            const auto amountOfLinesInFile = utils::getSplitLines(fileContent).size();
            amountOfLinesFromFiles += amountOfLinesInFile;
        }
    }
    return amountOfLinesFromFiles;
}

}
