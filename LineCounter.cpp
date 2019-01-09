#include "LineCounter.h"

std::vector<std::string> LineCounter::listOfFiles;

long LineCounter::getAmountOfLines(std::string dirPath)
{
	return calculateLines(dirPath);
}

long LineCounter::calculateLines(std::string dirPath)
{
	try
	{
		setListOfFiles(dirPath);
	}
	catch(std::string error)
	{
		std::cerr << error << std::endl;
	}

	long amountLines = 0;

	for (auto & file : listOfFiles)
	{
		for (auto & line : File::getLines(file))
		{
			amountLines++;
		}
	}

	return amountLines;
}

void LineCounter::setListOfFiles(std::string dirPath)
{
	listOfFiles.clear();
	fs::path directoryPath(dirPath);

	if (!fs::exists(directoryPath) || !fs::is_directory(directoryPath))
	{
		throw ("Folder: " + directoryPath.string() + " does not exist or is not a directiory");
	}

	std::cout << "Project name: " << directoryPath.filename() << std::endl;

	for (auto & p : fs::recursive_directory_iterator(directoryPath))
	{
		if (p.path().extension() == ".h" || p.path().extension() == ".cpp")
		{
			listOfFiles.push_back(p.path().string());
		}
	}
}

