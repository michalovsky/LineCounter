#pragma once

#include "ConfigFilePaths.h"
#include "FilePaths.h"

namespace lineCounter
{
class FilePathsSelector
{
public:
    virtual ~FilePathsSelector() = default;

    virtual FilePaths selectFilePaths(const ConfigFilePaths&) const = 0;
};
}