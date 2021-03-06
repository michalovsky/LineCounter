# LineCounter
Counts lines from files in given path.

<b>Get code</b>:

    git clone --recurse-submodules https://github.com/michalovsky/line-counter

<b>Include header:</b>
    
    #include "LineCounterApplication.h"

<b>Example of usage:</b>

    lineCounter::LineCounterApplication lineCounterApp;

    const std::vector<std::string> targetPathsToCountLinesIn = {"/home/michal/repos/rpg/src",
                                                               "/home/michal/repos/rpg/include"};
    const auto pathToFileWithPathsToIgnore =
        "/home/michal/repos/line-counter/exampleConfigFiles/examplePathsToIgnore.txt";
    const auto pathToFileWithExtensions =
        "/home/michal/repos/line-counter/exampleConfigFiles/exampleExtensions.txt";
    lineCounter::ConfigFilePaths configFilePaths{targetPathToCountLinesIn, pathToFileWithPathsToIgnore,
                                                 pathToFileWithExtensions};
    const auto amountOfLines = lineCounterApp.getAmountOfLines(configFilePaths);
    std::cout << "Amount of lines in paths:" << amountOfLines;
    
<b>Configuration of files:</b>
<ol>  
     <li>targetPathsToCountLinesIn - paths to files or directories where lines will be counted recursively</li>  
     <li>pathToFileWithPathsToIgnore - path to file that contains paths that will be ignored from counting lines</li> 
     <li>pathToFileWithExtensions - path to file that contains file extensions according to which files will be selected</li>  
</ol>  


Example configuration files are included in <i>exampleConfigFiles</i> folder:

Example content of <i>examplePathsToIgnore.txt</i>:
          
    /home/michal/repos/glossary/externals
    /somePath

Example content of <i>exampleExtensions.txt</i>:
    
    .cpp
    .h
