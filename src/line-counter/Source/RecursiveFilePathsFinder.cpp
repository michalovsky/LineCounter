#include "RecursiveFilePathsFinder.h"

#include <iostream>

#include "utils/exceptions/DirectoryNotFound.h"

namespace lineCounter
{

RecursiveFilePathsFinder::RecursiveFilePathsFinder(std::shared_ptr<utils::FileAccess> fileAccessInit)
    : fileAccess{std::move(fileAccessInit)}
{
}

FilePaths RecursiveFilePathsFinder::findFilePaths(const std::string& directoryPath) const
{
    return getAllPathsFromDirectory(directoryPath);
}

std::vector<std::string>
RecursiveFilePathsFinder::getAllPathsFromDirectory(const std::string& directoryPath) const
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