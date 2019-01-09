#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class File
{
	File() = delete;
public:
	/**
	* Returns all lines from file
	* @param absolute path to file
	* @return all lines from file
	*/
	static std::vector<std::string> getLines(std::string pathName);
private:
	static void open(std::string pathName);
	static void close();
	static std::fstream * file;
};

