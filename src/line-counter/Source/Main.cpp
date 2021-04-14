#include <iostream>

#include "LineCounterApplication.h"

int main()
{
    lineCounter::LineCounterApplication lineCounterApp;

    const std::vector<std::string> targetPathsToCountLinesIn = {"C:\\repos\\chimarrao-platformer\\src"};
    const auto pathToFileWithPathsToIgnore =
        "C:\\repos\\line-counter\\exampleConfigFiles\\examplePathsToIgnore.txt";
    const auto pathToFileWithExtensions =
        "C:\\repos\\line-counter\\exampleConfigFiles\\exampleExtensions.txt";
    lineCounter::ConfigFilePaths configFilePaths{targetPathsToCountLinesIn, pathToFileWithPathsToIgnore,
                                                 pathToFileWithExtensions};
    const auto amountOfLines = lineCounterApp.getAmountOfLines(configFilePaths);
    std::cout << "Amount of lines in paths:" << amountOfLines;
    return 0;
}
