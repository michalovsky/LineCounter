#include "gtest/gtest.h"

#include "utils/FileAccessMock.h"

#include "DefaultPathsToIgnoreReader.h"
#include "utils/exceptions/FileNotFound.h"

using namespace lineCounter;
using namespace ::testing;

namespace
{
const auto existingFilePath{"existing file path"};
const auto nonExistingFilePath{"non existing file path"};
const std::string fileWithIgnoredPathsContent{"/home/michal/\n/xxx/aaa/c.txt\nx.diff"};
const PathsToIgnore ignoredPaths{"/home/michal/", "/xxx/aaa/c.txt", "x.diff"};
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

    const auto actualIgnoredPaths = pathsToIgnoreReader.readPathsToIgnore(existingFilePath);

    ASSERT_EQ(actualIgnoredPaths, ignoredPaths);
}
