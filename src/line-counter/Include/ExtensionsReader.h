#pragma once

#include "FileExtensions.h"

namespace lineCounter
{
class ExtensionsReader
{
public:
    virtual ~ExtensionsReader() = default;

    virtual FileExtensions readExtensions(const std::string& filePath) const = 0;
};
}
