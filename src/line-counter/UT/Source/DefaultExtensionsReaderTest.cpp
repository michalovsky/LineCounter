#include "DefaultExtensionsReader.h"

#include "gtest/gtest.h"

#include "utils/FileAccessMock.h"

#include "utils/exceptions/FileNotFound.h"

using namespace lineCounter;
using namespace ::testing;

namespace
{
const auto existingFilePath{"existing file path"};
const auto nonExistingFilePath{"non existing file path"};
const std::string fileWithExtensionsContent{".cpp\n.h"};
const FileExtensions extensions{".cpp", ".h"};
}

class DefaultExtensionsReaderTest : public Test
{
public:
    std::shared_ptr<utils::FileAccessMock> fileAccess = std::make_shared<StrictMock<utils::FileAccessMock>>();
    DefaultExtensionsReader extensionsReader{fileAccess};
};

TEST_F(DefaultExtensionsReaderTest, givenNonExistingFilePath_shouldReturnNoExtensions)
{
    EXPECT_CALL(*fileAccess, readContent(nonExistingFilePath))
        .WillOnce(Throw(utils::exceptions::FileNotFound{""}));

    const auto actualExtensions = extensionsReader.readExtensions(nonExistingFilePath);

    ASSERT_TRUE(actualExtensions.empty());
}

TEST_F(DefaultExtensionsReaderTest, givenExistingDirectoryPath_shouldReturnExtensionsContainedInThisFile)
{
    EXPECT_CALL(*fileAccess, readContent(existingFilePath)).WillOnce(Return(fileWithExtensionsContent));

    const auto actualExtensions = extensionsReader.readExtensions(existingFilePath);

    ASSERT_EQ(actualExtensions, extensions);
}
