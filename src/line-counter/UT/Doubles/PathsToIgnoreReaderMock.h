#pragma once

#include "gmock/gmock.h"

#include "PathsToIgnoreReader.h"

namespace lineCounter
{
class PathsToIgnoreReaderMock : public PathsToIgnoreReader
{
public:
    MOCK_CONST_METHOD1(readPathsToIgnore, PathsToIgnore(const std::string& filepath));
};
}