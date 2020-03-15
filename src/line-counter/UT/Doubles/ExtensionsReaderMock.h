#pragma once

#include "gmock/gmock.h"

#include "ExtensionsReader.h"

namespace lineCounter
{
class ExtensionsReaderMock : public ExtensionsReader
{
public:
    MOCK_CONST_METHOD1(readExtensions, FileExtensions(const std::string& filePath));
};
}