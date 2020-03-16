#include "RecursiveFilePathsFinder.h"

#include <algorithm>
#include <iostream>

#include "utils/exceptions/DirectoryNotFound.h"

namespace lineCounter
{

RecursiveFilePathsFinder::RecursiveFilePathsFinder(std::shared_ptr<utils::FileAccess> fileAccessInit)
    : fileAccess{std::move(fileAccessInit)}
{
}

FilePaths RecursiveFilePathsFinder::findFilePaths(const Paths& pathsToSearch) const
{
    FilePaths filePaths;
    for (const auto& pathToSearch : pathsToSearch)
    {
        const auto filePathsInPath = findFilePathsInPath(pathToSearch);
        filePaths.insert(filePaths.end(), filePathsInPath.begin(), filePathsInPath.end());
    }
    return filePaths;
}

FilePaths RecursiveFilePathsFinder::findFilePathsInPath(const Path& pathToSearch) const
{
    if (pathIsFile(pathToSearch))
    {
        return FilePaths{pathToSearch};
    }
    return getAllFilePathsFromDirectory(pathToSearch);
}

bool RecursiveFilePathsFinder::pathIsFile(const Path& path) const
{
    return fileAccess->isRegularFile(path);
}

FilePaths RecursiveFilePathsFinder::getAllFilePathsFromDirectory(const Path& directoryPath) const
{
    auto pathsFromDirectory = getAllPathsFromDirectory(directoryPath);
    pathsFromDirectory.erase(std::remove_if(pathsFromDirectory.begin(), pathsFromDirectory.end(),
                                            [&](const Path& path) { return not pathIsFile(path); }),
                             pathsFromDirectory.end());
    return pathsFromDirectory;
}

Paths RecursiveFilePathsFinder::getAllPathsFromDirectory(const Path& directoryPath) const
{
    try
    {
        return fileAccess->getAllPathsFromDirectory(directoryPath);
    }
    catch (const utils::exceptions::DirectoryNotFound& e)
    {
        std::cerr << "Error while reading paths from directory:" << e.what();
        return {};
    }
}

}