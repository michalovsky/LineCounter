#include "RecursiveFilePathsFinder.h"

#include "gtest/gtest.h"

#include "utils/FileAccessMock.h"

#include "utils/exceptions/DirectoryNotFound.h"

using namespace lineCounter;
using namespace ::testing;

namespace
{
template <class T>
static bool compareVectors(std::vector<T> a, std::vector<T> b)
{
    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());
    return (a == b);
}
const Path pathToSearch1{"pathToSearch1"};
const Path pathToSearch2{"pathToSearch2"};
const Path nonExistingPathToSearch{"nonExistingPathToSearch"};
const Paths pathsToSearch{pathToSearch1, pathToSearch2};
const Paths pathsToSearchWithOnePath{pathToSearch1};
const Paths pathsToSearchWithNonExistingPath{pathToSearch1, nonExistingPathToSearch};
const FilePath filePath1{"filePath1"};
const FilePath filePath2{"filePath2"};
const FilePath filePath3{"filePath3"};
const FilePath filePath4{"filePath4"};
const FilePaths filePaths{filePath1, filePath2};
const FilePaths filePaths2{filePath3, filePath4};
const FilePaths concatenatedFilePaths{filePath1, filePath2, filePath3, filePath4};
const FilePaths filePathsWithOneFilePath{filePath1};
const FilePaths filePathsWithTwoFilePath{pathToSearch1, pathToSearch2};
}

class RecursiveFilePathsFinderTest : public Test
{
public:
    std::shared_ptr<utils::FileAccessMock> fileAccess = std::make_shared<StrictMock<utils::FileAccessMock>>();
    RecursiveFilePathsFinder filePathsFinder{fileAccess};
};

TEST_F(RecursiveFilePathsFinderTest, givenPathsWhichAreFiles_shouldReturnFilePathsWithTwoFilePath)
{
    EXPECT_CALL(*fileAccess, isRegularFile(pathToSearch1)).WillOnce(Return(true));
    EXPECT_CALL(*fileAccess, isRegularFile(pathToSearch2)).WillOnce(Return(true));

    const auto actualFilePaths = filePathsFinder.findFilePaths(pathsToSearch);

    ASSERT_EQ(actualFilePaths, filePathsWithTwoFilePath);
}

TEST_F(RecursiveFilePathsFinderTest,
       givenOneExistingPathAndOneNonExisting_shouldReturnFilePathsFromExistingDirectory)
{
    EXPECT_CALL(*fileAccess, isRegularFile(pathToSearch1)).WillOnce(Return(false));
    EXPECT_CALL(*fileAccess, getAllPathsFromDirectory(pathToSearch1)).WillOnce(Return(filePaths));
    EXPECT_CALL(*fileAccess, isRegularFile(filePath1)).WillOnce(Return(true));
    EXPECT_CALL(*fileAccess, isRegularFile(filePath2)).WillOnce(Return(false));
    EXPECT_CALL(*fileAccess, isRegularFile(nonExistingPathToSearch)).WillOnce(Return(false));
    EXPECT_CALL(*fileAccess, getAllPathsFromDirectory(nonExistingPathToSearch))
        .WillOnce(Throw(utils::exceptions::DirectoryNotFound{""}));

    const auto actualFilePaths = filePathsFinder.findFilePaths(pathsToSearchWithNonExistingPath);

    ASSERT_EQ(actualFilePaths, filePathsWithOneFilePath);
}

TEST_F(RecursiveFilePathsFinderTest, givenExistingDirectoryPaths_shouldReturnAllFilePathsFromThisDirectories)
{
    EXPECT_CALL(*fileAccess, isRegularFile(pathToSearch1)).WillOnce(Return(false));
    EXPECT_CALL(*fileAccess, getAllPathsFromDirectory(pathToSearch1)).WillOnce(Return(filePaths));
    EXPECT_CALL(*fileAccess, isRegularFile(filePath1)).WillOnce(Return(true));
    EXPECT_CALL(*fileAccess, isRegularFile(filePath2)).WillOnce(Return(true));

    EXPECT_CALL(*fileAccess, isRegularFile(pathToSearch2)).WillOnce(Return(false));
    EXPECT_CALL(*fileAccess, getAllPathsFromDirectory(pathToSearch2)).WillOnce(Return(filePaths2));
    EXPECT_CALL(*fileAccess, isRegularFile(filePath3)).WillOnce(Return(true));
    EXPECT_CALL(*fileAccess, isRegularFile(filePath4)).WillOnce(Return(true));

    const auto actualFilePaths = filePathsFinder.findFilePaths(pathsToSearch);

    ASSERT_TRUE(compareVectors(actualFilePaths, concatenatedFilePaths));
}
