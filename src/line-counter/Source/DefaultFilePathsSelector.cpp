#include "DefaultFilePathsSelector.h"

#include <algorithm>

#include "boost/algorithm/cxx11/any_of.hpp"
#include "boost/algorithm/string/predicate.hpp"

using namespace boost::algorithm;

namespace lineCounter
{

DefaultFilePathsSelector::DefaultFilePathsSelector(
    std::unique_ptr<FilePathsFinder> filePathsFinderInit,
    std::unique_ptr<PathsToIgnoreReader> pathsToIgnoreReaderInit,
    std::unique_ptr<ExtensionsReader> extensionsReaderInit)
    : filePathFinder{std::move(filePathsFinderInit)},
      pathsToIgnoreReader{std::move(pathsToIgnoreReaderInit)},
      extensionReader{std::move(extensionsReaderInit)}
{
}

FilePaths DefaultFilePathsSelector::selectFilePaths(const ConfigFilePaths& configFilePaths) const
{
    auto filePaths = filePathFinder->findFilePaths(configFilePaths.targetPathsToCountLinesIn);
    const auto pathsToIgnore = readPathsToIgnore(configFilePaths.pathToFileWithPathsToIgnore);
    const auto fileExtensions = readExtensions(configFilePaths.pathToFileWithExtensions);
    deleteFilePathsContainingPathToIgnore(filePaths, pathsToIgnore);
    if (not fileExtensions.empty())
    {
        deleteFilePathsWithoutSpecificExtensions(filePaths, fileExtensions);
    }
    return filePaths;
}

PathsToIgnore
DefaultFilePathsSelector::readPathsToIgnore(const std::string& pathToFileWithPathsToIgnore) const
{
    if (pathToFileWithPathsToIgnore.empty())
    {
        return {};
    }
    return pathsToIgnoreReader->readPathsToIgnore(pathToFileWithPathsToIgnore);
}

FileExtensions DefaultFilePathsSelector::readExtensions(const std::string& pathToFileWithExtensions) const
{
    if (pathToFileWithExtensions.empty())
    {
        return {};
    }
    return extensionReader->readExtensions(pathToFileWithExtensions);
}

void DefaultFilePathsSelector::deleteFilePathsContainingPathToIgnore(FilePaths& filePaths,
                                                                     const PathsToIgnore& pathsToIgnore) const
{
    filePaths.erase(std::remove_if(filePaths.begin(), filePaths.end(),
                                   [&](std::string& filePath) {
                                       return filePathContainsPathToIgnore(filePath, pathsToIgnore);
                                   }),
                    filePaths.end());
}

void DefaultFilePathsSelector::deleteFilePathsWithoutSpecificExtensions(
    FilePaths& filePaths, const FileExtensions& extensions) const
{
    filePaths.erase(std::remove_if(filePaths.begin(), filePaths.end(),
                                   [&](std::string& filePath) {
                                       return not filePathHasSpecificExtension(filePath, extensions);
                                   }),
                    filePaths.end());
}

bool DefaultFilePathsSelector::filePathContainsPathToIgnore(const std::string& filePath,
                                                            const PathsToIgnore& pathsToIgnore) const
{
    return any_of(pathsToIgnore, [&](const std::string& pathToIgnore) {
        return filePath.find(pathToIgnore) != std::string::npos;
    });
}

bool DefaultFilePathsSelector::filePathHasSpecificExtension(const std::string& filePath,
                                                            const FileExtensions& extensions) const
{
    return any_of(extensions, [&](const std::string& extension) { return ends_with(filePath, extension); });
}

}