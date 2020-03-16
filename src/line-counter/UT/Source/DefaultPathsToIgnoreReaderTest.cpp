#include "DefaultPathsToIgnoreReader.h"

#include "gtest/gtest.h"

#include "utils/FileAccessMock.h"

#include "utils/exceptions/FileNotFound.h"

using namespace lineCounter;
using namespace ::testing;

namespace
{
const auto existingFilePath{"existing file path"};
const auto nonExistingFilePath{"non existing file path"};
const std::string path1{"/home/michal/"};
const std::string path2{"x.diff"};
const std::string invalidPath{"invalid path"};
const std::string newLine{"\n"};
const std::string fileWithIgnoredPathsContent{path1 + newLine + path2 + newLine + invalidPath};
const PathsToIgnore ignoredPaths{path1, path2};
}

class DefaultPathsToIgnoreReaderTest : public Test
{
public:
    std::shared_ptr<utils::FileAccessMock> fileAccess = std::make_shared<StrictMock<utils::FileAccessMock>>();
    DefaultPathsToIgnoreReader pathsToIgnoreReader{fileAccess};
};

TEST_F(DefaultPathsToIgnoreReaderTest, givenNonExistingFilePath_shouldReturnNoIgnoredPaths)
{
    EXPECT_CALL(*fileAccess, readContent(nonExistingFilePath))
        .WillOnce(Throw(utils::exceptions::FileNotFound{""}));

    const auto actualIgnoredPaths = pathsToIgnoreReader.readPathsToIgnore(nonExistingFilePath);

    ASSERT_TRUE(actualIgnoredPaths.empty());
}

TEST_F(DefaultPathsToIgnoreReaderTest, givenExistingFilePath_shouldReturnIgnoredPathsContainedInFile)
{
    EXPECT_CALL(*fileAccess, readContent(existingFilePath)).WillOnce(Return(fileWithIgnoredPathsContent));
    EXPECT_CALL(*fileAccess, isRegularFile(path1)).WillOnce(Return(false));
    EXPECT_CALL(*fileAccess, isDirectory(path1)).WillOnce(Return(true));
    EXPECT_CALL(*fileAccess, isRegularFile(path2)).WillOnce(Return(true));
    EXPECT_CALL(*fileAccess, isRegularFile(invalidPath)).WillOnce(Return(false));
    EXPECT_CALL(*fileAccess, isDirectory(invalidPath)).WillOnce(Return(false));

    const auto actualIgnoredPaths = pathsToIgnoreReader.readPathsToIgnore(existingFilePath);

    ASSERT_EQ(actualIgnoredPaths, ignoredPaths);
}
