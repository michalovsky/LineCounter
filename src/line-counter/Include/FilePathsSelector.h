#pragma once

#include "FilePaths.h"
#include "ConfigFilePaths.h"

namespace lineCounter
{
class FilePathsSelector
{
public:
    virtual ~FilePathsSelector() = default;

    virtual FilePaths selectFilePaths(const ConfigFilePaths&) const = 0;
};
}