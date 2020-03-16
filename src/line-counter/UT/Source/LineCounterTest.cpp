#include "LineCounter.h"

#include "gtest/gtest.h"

#include "FilePathsSelectorMock.h"
#include "utils/FileAccessMock.h"

using namespace ::testing;
using namespace lineCounter;

namespace
{
const auto targetPath{"targetPath"};
const std::string pathToFileWithPathsToIgnore{"pathToFileWithPathsToIgnore"};
const std::string pathToFileWithExtensions{"pathToFileWithExtensions"};
const ConfigFilePaths configFilePaths{targetPath, pathToFileWithPathsToIgnore, pathToFileWithExtensions};
const auto file1Path{"file1Path"};
const auto file1Content{""};
const auto file2Path{"file2Path"};
const auto file2Content{"a\nb\nc"};
const auto file3Path{"file3Path"};
const auto file3Content{"1\n2"};
const FilePaths filePaths{file1Path, file2Path, file3Path};
const auto expectedAmountOfLines{5};
}

class LineCounterTest : public Test
{
public:
    std::unique_ptr<FilePathsSelectorMock> filePathsSelectorInit =
        std::make_unique<StrictMock<FilePathsSelectorMock>>();
    FilePathsSelectorMock* filePathsSelector = filePathsSelectorInit.get();
    std::shared_ptr<utils::FileAccessMock> fileAccess = std::make_shared<StrictMock<utils::FileAccessMock>>();
    LineCounter lineCounter{std::move(filePathsSelectorInit), fileAccess};
};

TEST_F(LineCounterTest, shouldReturnAmountOfLinesFromFilePaths)
{
    EXPECT_CALL(*filePathsSelector, selectFilePaths(configFilePaths)).WillOnce(Return(filePaths));
    EXPECT_CALL(*fileAccess, readContent(file1Path)).WillOnce(Return(file1Content));
    EXPECT_CALL(*fileAccess, readContent(file2Path)).WillOnce(Return(file2Content));
    EXPECT_CALL(*fileAccess, readContent(file3Path)).WillOnce(Return(file3Content));

    const auto actualAmountOfLines = lineCounter.getAmountOfLines(configFilePaths);

    ASSERT_EQ(actualAmountOfLines, expectedAmountOfLines);
}
