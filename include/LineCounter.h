#pragma once
#include "File.h"
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

class LineCounter
{
	LineCounter() = delete;
public:
	/**
	 * Returns amount of lines from given directory
	 * @param absolute path to directory
	 * @return amount of lines from given directory
	 */
	static long getAmountOfLines(std::string dirPath);
private:
	static long calculateLines(std::string dirPath);
	static void setListOfFiles(std::string dirPath);
	static std::vector<std::string> listOfFiles;
};

