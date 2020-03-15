#include "DefaultFilePathsSelector.h"

#include "boost/algorithm/cxx11/all_of.hpp"
#include "boost/algorithm/cxx11/any_of.hpp"
#include "gtest/gtest.h"
#include "algorithm"

#include "ExtensionsReaderMock.h"
#include "FilePathsFinderMock.h"
#include "PathsToIgnoreReaderMock.h"

using namespace lineCounter;
using namespace ::testing;
using namespace boost::algorithm;

namespace
{
template <class T>
static bool compareVectors(std::vector<T> a, std::vector<T> b)
{
    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());
    return (a == b);
}
const auto targetPath{"targetPath"};
const auto pathToFileWithPathsToIgnore{"pathToFileWithPathsToIgnore"};
const auto pathToFileWithExtensions{"pathToFileWithExtensions"};
const ConfigFilePaths configFilePaths{targetPath, pathToFileWithPathsToIgnore, pathToFileWithExtensions};
const PathsToIgnore noPathsToIgnore{};
const PathsToIgnore pathsToIgnore{"line-counter/"};
const FileExtensions extensions{".cpp", ".h"};
const FilePaths filePaths{"/home/michal/line-counter/Main.cpp", "/home/michal/xxxx", "aaa.pdf", "c.diff",
                          "glossary.h"};
const FilePaths filePathsWithSelectedExtensions{"/home/michal/line-counter/Main.cpp", "glossary.h"};
const FilePaths filePathsWithSelectedExtensionsAndPathToIgnore{"glossary.h"};
}

class DefaultFilePathsSelectorTest : public Test
{
public:
    std::unique_ptr<FilePathsFinderMock> filePathsFinderInit =
        std::make_unique<StrictMock<FilePathsFinderMock>>();
    FilePathsFinderMock* filePathsFinder = filePathsFinderInit.get();
    std::unique_ptr<PathsToIgnoreReaderMock> pathsToIgnoreReaderInit =
        std::make_unique<StrictMock<PathsToIgnoreReaderMock>>();
    PathsToIgnoreReaderMock* pathsToIgnoreReader = pathsToIgnoreReaderInit.get();
    std::unique_ptr<ExtensionsReaderMock> extensionsReaderInit =
        std::make_unique<StrictMock<ExtensionsReaderMock>>();
    ExtensionsReaderMock* extensionsReader = extensionsReaderInit.get();
    DefaultFilePathsSelector selector{std::move(filePathsFinderInit), std::move(pathsToIgnoreReaderInit),
                                      std::move(extensionsReaderInit)};
};

TEST_F(DefaultFilePathsSelectorTest,
       givenEmptyPathsToIgnoreAndSpecificExtensions_shouldSelectAppropriateFilePaths)
{
    EXPECT_CALL(*filePathsFinder, findFilePaths(targetPath)).WillOnce(Return(filePaths));
    EXPECT_CALL(*pathsToIgnoreReader, readPathsToIgnore(pathToFileWithPathsToIgnore))
        .WillOnce(Return(noPathsToIgnore));
    EXPECT_CALL(*extensionsReader, readExtensions(pathToFileWithExtensions))
        .WillOnce(Return(extensions));

    const auto actualFilePaths = selector.selectFilePaths(configFilePaths);

    ASSERT_TRUE(compareVectors(actualFilePaths, filePathsWithSelectedExtensions));
}

TEST_F(DefaultFilePathsSelectorTest, givenPathsToIgnoreAndSpecificExtensions_shouldSelectAppropriateFilePaths)
{
    EXPECT_CALL(*filePathsFinder, findFilePaths(targetPath)).WillOnce(Return(filePaths));
    EXPECT_CALL(*pathsToIgnoreReader, readPathsToIgnore(pathToFileWithPathsToIgnore))
        .WillOnce(Return(pathsToIgnore));
    EXPECT_CALL(*extensionsReader, readExtensions(pathToFileWithExtensions))
        .WillOnce(Return(extensions));

    const auto actualFilePaths = selector.selectFilePaths(configFilePaths);

    ASSERT_TRUE(compareVectors(actualFilePaths, filePathsWithSelectedExtensionsAndPathToIgnore));
}