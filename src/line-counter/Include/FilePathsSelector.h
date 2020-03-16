#pragma once

#include "ConfigFilePaths.h"
#include "Paths.h"

namespace lineCounter
{
class FilePathsSelector
{
public:
    virtual ~FilePathsSelector() = default;

    virtual FilePaths selectFilePaths(const ConfigFilePaths&) const = 0;
};
}