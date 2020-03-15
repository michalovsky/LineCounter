#include "RecursiveFilePathsFinder.h"

#include "gtest/gtest.h"

#include "utils/FileAccessMock.h"

#include "utils/exceptions/DirectoryNotFound.h"

using namespace lineCounter;
using namespace ::testing;

namespace
{
const auto existingDirectoryPath{"existing directory path"};
const auto nonExistingDirectoryPath{"non existing directory path"};
const auto existingFilePath{"file path"};
const FilePaths filePaths{"filepath1", "filepath2"};
const FilePaths filePathsWithSingleFilePath{"file path"};
}

class RecursiveFilePathsFinderTest : public Test
{
public:
    std::shared_ptr<utils::FileAccessMock> fileAccess = std::make_shared<StrictMock<utils::FileAccessMock>>();
    RecursiveFilePathsFinder filePathsFinder{fileAccess};
};

TEST_F(RecursiveFilePathsFinderTest, givenFilePath_shouldReturnFilePathsWithOneFilePath)
{
    EXPECT_CALL(*fileAccess, isRegularFile(existingFilePath)).WillOnce(Return(true));

    const auto actualFilePaths = filePathsFinder.findFilePaths(existingFilePath);

    ASSERT_EQ(actualFilePaths, filePathsWithSingleFilePath);
}

TEST_F(RecursiveFilePathsFinderTest, givenNonExistingDirectoryPath_shouldReturnEmptyFilePaths)
{
    EXPECT_CALL(*fileAccess, isRegularFile(nonExistingDirectoryPath)).WillOnce(Return(false));
    EXPECT_CALL(*fileAccess, getAllFilenamesFromDirectory(nonExistingDirectoryPath))
        .WillOnce(Throw(utils::exceptions::DirectoryNotFound{""}));

    const auto actualFilePaths = filePathsFinder.findFilePaths(nonExistingDirectoryPath);

    ASSERT_TRUE(actualFilePaths.empty());
}

TEST_F(RecursiveFilePathsFinderTest, givenExistingDirectoryPath_shouldReturnAllFilePathsFromThisDirectory)
{
    EXPECT_CALL(*fileAccess, isRegularFile(existingDirectoryPath)).WillOnce(Return(false));
    EXPECT_CALL(*fileAccess, getAllFilenamesFromDirectory(existingDirectoryPath)).WillOnce(Return(filePaths));

    const auto actualFilePaths = filePathsFinder.findFilePaths(existingDirectoryPath);

    ASSERT_EQ(actualFilePaths, filePaths);
}
