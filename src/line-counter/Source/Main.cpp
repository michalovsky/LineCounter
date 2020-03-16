#include <iostream>

#include "LineCounterApplication.h"

int main()
{
    lineCounter::LineCounterApplication lineCounterApp;

    std::string targetPathToCountLinesIn = "/home/michal/repos/glossary/src";
    std::string pathToFileWithPathsToIgnore = "";
    std::string pathToFileWithExtensions = "/home/michal/repos/extensions.txt";
    lineCounter::ConfigFilePaths configFilePaths{targetPathToCountLinesIn, pathToFileWithPathsToIgnore, pathToFileWithExtensions};
    auto amountOfLines = lineCounterApp.getAmountOfLines(configFilePaths);
    std::cout << "Amount of lines in path: "<<targetPathToCountLinesIn <<" = "<< amountOfLines;
    return 0;
}
