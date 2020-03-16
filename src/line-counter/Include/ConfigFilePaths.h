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

inline bool operator==(const ConfigFilePaths& ls, const ConfigFilePaths& rs)
{
    return ls.targetPathToCountLinesIn == rs.targetPathToCountLinesIn &&
           ls.pathToFileWithExtensions == rs.pathToFileWithExtensions &&
           ls.pathToFileWithPathsToIgnore == rs.pathToFileWithPathsToIgnore;
}

}