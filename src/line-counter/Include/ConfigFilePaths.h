#pragma once

#include <string>

namespace lineCounter
{
struct ConfigFilePaths
{
    std::string targetPathToCountLinesIn;
    std::string pathToFileWithPathsToIgnore;
    std::string pathToFileWithExtensions;
};
}