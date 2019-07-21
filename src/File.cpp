#include "File.h"

std::fstream * File::file(nullptr);

std::vector<std::string> File::getLines(std::string pathName)
{
	std::vector<std::string> lines;

	try
	{
		open(pathName);
	}
	catch (std::string error)
	{
		std::cerr << error << std::endl << "Returning empty string vector" << std::endl;
		return lines;
	}

	std::string line;
	while (file->good() && std::getline(*file,line))
	{
		lines.push_back(line);
	}
	close();
	return lines;
}

void File::open(std::string pathName)
{
	file = new std::fstream(pathName.c_str(), std::ios::in);
	if (!file->is_open()) throw ("Cant open " + pathName + " file");
	if (file->fail()) throw ("Failed: " + pathName);
}

void File::close()
{
	delete file;
}

