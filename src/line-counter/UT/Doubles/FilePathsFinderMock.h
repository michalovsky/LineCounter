#pragma once

#include "gmock/gmock.h"

#include "FilePathsFinder.h"

namespace lineCounter
{
class FilePathsFinderMock : public FilePathsFinder
{
public:
    MOCK_CONST_METHOD1(findFilePaths, FilePaths(const std::string& directoryPath));
};
}