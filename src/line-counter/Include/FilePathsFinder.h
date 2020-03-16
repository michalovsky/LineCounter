#pragma once

#include "Paths.h"

namespace lineCounter
{
class FilePathsFinder
{
public:
    virtual ~FilePathsFinder() = default;

    virtual FilePaths findFilePaths(const Paths&) const = 0;
};
}