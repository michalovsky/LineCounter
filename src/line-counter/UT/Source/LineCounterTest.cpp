#include "LineCounter.h"

#include "gtest/gtest.h"

#include "FilePathsSelectorMock.h"
#include "utils/FileAccessMock.h"

using namespace ::testing;
using namespace lineCounter;

class LineCounterTest : public Test
{
public:
    std::unique_ptr<FilePathsSelectorMock> filePathsSelectorInit =
        std::make_unique<StrictMock<FilePathsSelectorMock>>();
    FilePathsSelectorMock* filePathsSelector = filePathsSelectorInit.get();
    std::shared_ptr<utils::FileAccessMock> fileAccess = std::make_shared<StrictMock<utils::FileAccessMock>>();
    LineCounter lineCounter{std::move(filePathsSelectorInit), fileAccess};
};

TEST_F(LineCounterTest, ccc)
{
    //    const auto amountOfLines = lineCounter.getAmountOfLines()
}
