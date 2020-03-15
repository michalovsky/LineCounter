#include "RecursiveFilePathsFinder.h"

#include "utils/exceptions/DirectoryNotFound.h"

#include "gtest/gtest.h"

#include "utils/FileAccessMock.h"

using namespace lineCounter;
using namespace ::testing;

namespace
{
const auto existingDirectoryPath{"existing directory path"};
const auto nonExistingDirectoryPath{"non existing directory path"};
const FilePaths filePaths{"filepath1", "filepath2"};
}

class RecursiveFilePathsFinderTest : public Test
{
public:
    std::shared_ptr<utils::FileAccessMock> fileAccess = std::make_shared<StrictMock<utils::FileAccessMock>>();
    RecursiveFilePathsFinder filePathsFinder{fileAccess};
};

TEST_F(RecursiveFilePathsFinderTest, givenNonExistingDirectoryPath_shouldReturnEmptyFilePaths)
{
    EXPECT_CALL(*fileAccess, getAllPathsFromDirectory(nonExistingDirectoryPath)).WillOnce(Throw(utils::exceptions::DirectoryNotFound{""}));

    const auto actualFilePaths = filePathsFinder.findFilePaths(nonExistingDirectoryPath);

    ASSERT_TRUE(actualFilePaths.empty());
}

TEST_F(RecursiveFilePathsFinderTest, givenExistingDirectoryPath_shouldReturnAllFilePathsFromThisDirectory)
{
    EXPECT_CALL(*fileAccess, getAllPathsFromDirectory(existingDirectoryPath)).WillOnce(Return(filePaths));

    const auto actualFilePaths = filePathsFinder.findFilePaths(existingDirectoryPath);

    ASSERT_EQ(actualFilePaths, filePaths);
}
