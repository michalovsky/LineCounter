#pragma once

#include "PathsToIgnore.h"

namespace lineCounter
{

class PathsToIgnoreReader
{
public:
    virtual ~PathsToIgnoreReader() = default;

    virtual PathsToIgnore readPathsToIgnore(const std::string& filePath) const = 0;
};

}