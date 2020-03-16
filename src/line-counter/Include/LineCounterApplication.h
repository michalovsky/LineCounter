#pragma once

#include <memory>

#include "LineCounter.h"
#include "utils/FileAccess.h"

namespace lineCounter
{

class LineCounterApplication
{
public:
    LineCounterApplication();

    long getAmountOfLines(const ConfigFilePaths&) const;

private:
    void initializeLineCounter();

    std::unique_ptr<LineCounter> lineCounter;
};

}
