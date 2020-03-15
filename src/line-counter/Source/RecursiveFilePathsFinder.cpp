#include "RecursiveFilePathsFinder.h"

#include <iostream>

#include "utils/exceptions/DirectoryNotFound.h"

namespace lineCounter
{

RecursiveFilePathsFinder::RecursiveFilePathsFinder(std::shared_ptr<utils::FileAccess> fileAccessInit)
    : fileAccess{std::move(fileAccessInit)}
{
}

FilePaths RecursiveFilePathsFinder::findFilePaths(const std::string& path) const
{
    if (pathIsFile(path))
    {
        return FilePaths{path};
    }
    return getAllPathsFromDirectory(path);
}

bool RecursiveFilePathsFinder::pathIsFile(const std::string& path) const
{
    return fileAccess->isRegularFile(path);
}

FilePaths RecursiveFilePathsFinder::getAllPathsFromDirectory(const std::string& directoryPath) const
{
    try
    {
        return fileAccess->getAllFilenamesFromDirectory(directoryPath);
    }
    catch (const utils::exceptions::DirectoryNotFound& e)
    {
        std::cerr << "Error while reading paths from directory:" << e.what();
        return {};
    }
}

}