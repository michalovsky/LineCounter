#pragma once

#include "gmock/gmock.h"

#include "FilePathsSelector.h"

namespace lineCounter
{
class FilePathsSelectorMock : public FilePathsSelector
{
public:
    MOCK_CONST_METHOD1(selectFilePaths, FilePaths(const ConfigFilePaths&));
};
}