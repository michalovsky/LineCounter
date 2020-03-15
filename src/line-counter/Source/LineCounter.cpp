#include "LineCounter.h"

namespace lineCounter
{
LineCounter::LineCounter(std::unique_ptr<FilePathsSelector> filePathsSelectorInit,
                         std::shared_ptr<utils::FileAccess> fileAccessInit)
    : filePathsSelector{std::move(filePathsSelectorInit)}, fileAccess{std::move(fileAccessInit)}
{
}

long LineCounter::getAmountOfLines(const std::string& dirPath) const
{
    return calculateLines(dirPath);
}

long LineCounter::calculateLines(const std::string&) const
{
    return 0;
    //    try
    //    {
    //        setListOfFiles(dirPath);
    //    }
    //    catch(std::string error)
    //    {
    //        std::cerr << error << std::endl;
    //    }
    //
    //    long amountLines = 0;
    //
    //    for (auto & file : listOfFiles)
    //    {
    //        for (auto & line : File::getLines(file))
    //        {
    //            amountLines++;
    //        }
    //    }
    //
    //    return amountLines;
}

std::vector<std::string> LineCounter::getFilePathsFromDirectory(const std::string&) const
{
    return {};
    //    fs::path directoryPath(dirPath);
    //
    //    if (!fs::exists(directoryPath) || !fs::is_directory(directoryPath))
    //    {
    //        throw ("Folder: " + directoryPath.string() + " does not exist or is not a directiory");
    //    }
    //
    //    std::cout << "Project name: " << directoryPath.filename() << std::endl;
    //
    //    for (auto & p : fs::recursive_directory_iterator(directoryPath))
    //    {
    //        if (p.path().extension() == ".h" || p.path().extension() == ".cpp")
    //        {
    //            listOfFiles.push_back(p.path().string());
    //        }
    //    }
}
}
