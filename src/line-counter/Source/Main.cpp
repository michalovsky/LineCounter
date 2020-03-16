#include <iostream>

#include "LineCounterApplication.h"

int main()
{
    lineCounter::LineCounterApplication lineCounterApp;

    const auto targetPathToCountLinesIn = "/home/michal/repos/glossary/src";
    const auto pathToFileWithPathsToIgnore =
        "/home/michal/repos/line-counter/exampleConfigFiles/examplePathsToIgnore.txt";
    const auto pathToFileWithExtensions =
        "/home/michal/repos/line-counter/exampleConfigFiles/exampleExtensions.txt";
    lineCounter::ConfigFilePaths configFilePaths{targetPathToCountLinesIn, pathToFileWithPathsToIgnore,
                                                 pathToFileWithExtensions};
    const auto amountOfLines = lineCounterApp.getAmountOfLines(configFilePaths);
    std::cout << "Amount of lines in path: " << targetPathToCountLinesIn << " = " << amountOfLines;
    return 0;
}
