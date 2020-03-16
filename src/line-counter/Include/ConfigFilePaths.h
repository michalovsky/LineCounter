#pragma once

#include <string>
#include <vector>

namespace lineCounter
{
struct ConfigFilePaths
{
    std::vector<std::string> targetPathsToCountLinesIn;
    std::string pathToFileWithPathsToIgnore;
    std::string pathToFileWithExtensions;
};

inline bool operator==(const ConfigFilePaths& ls, const ConfigFilePaths& rs)
{
    return ls.targetPathsToCountLinesIn == rs.targetPathsToCountLinesIn &&
           ls.pathToFileWithExtensions == rs.pathToFileWithExtensions &&
           ls.pathToFileWithPathsToIgnore == rs.pathToFileWithPathsToIgnore;
}

}