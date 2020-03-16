#include <iostream>

#include "LineCounterApplication.h"

int main()
{
    lineCounter::LineCounterApplication lineCounterApp;

    const std::vector<std::string> targetPathsToCountLinesIn = {"/home/michal/repos/rpg/src",
                                                               "/home/michal/repos/rpg/include"};
    const auto pathToFileWithPathsToIgnore =
        "/home/michal/repos/line-counter/exampleConfigFiles/examplePathsToIgnore.txt";
    const auto pathToFileWithExtensions =
        "/home/michal/repos/line-counter/exampleConfigFiles/exampleExtensions.txt";
    lineCounter::ConfigFilePaths configFilePaths{targetPathsToCountLinesIn, pathToFileWithPathsToIgnore,
                                                 pathToFileWithExtensions};
    const auto amountOfLines = lineCounterApp.getAmountOfLines(configFilePaths);
    std::cout << "Amount of lines in paths:" << amountOfLines;
    return 0;
}
