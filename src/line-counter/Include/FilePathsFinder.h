#pragma once

#include "FilePaths.h"

namespace lineCounter
{
class FilePathsFinder
{
public:
    virtual ~FilePathsFinder() = default;

    virtual FilePaths findFilePaths(const std::string& directoryPath) const = 0;
};
}