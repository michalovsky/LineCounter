#pragma once

#include <memory>

#include "ExtensionsReader.h"
#include "FilePathsFinder.h"
#include "FilePathsSelector.h"
#include "PathsToIgnoreReader.h"

namespace lineCounter
{
class DefaultFilePathsSelector : public FilePathsSelector
{
public:
    DefaultFilePathsSelector(std::unique_ptr<FilePathsFinder>, std::unique_ptr<PathsToIgnoreReader>,
                             std::unique_ptr<ExtensionsReader>);

    FilePaths selectFilePaths(const ConfigFilePaths&) const override;

private:
    void deleteFilePathsContainingPathToIgnore(FilePaths&, const PathsToIgnore&) const;
    void deleteFilePathsWithoutSpecificExtensions(FilePaths&, const FileExtensions&) const;
    bool filePathContainsPathToIgnore(const std::string&, const PathsToIgnore&) const;
    bool filePathHasSpecificExtension(const std::string&, const FileExtensions&) const;

    std::unique_ptr<FilePathsFinder> filePathFinder;
    std::unique_ptr<PathsToIgnoreReader> pathsToIgnoreReader;
    std::unique_ptr<ExtensionsReader> extensionReader;
};
}