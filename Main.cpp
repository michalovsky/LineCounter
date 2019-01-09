#include "LineCounter.h"

int main()
{
	//Example
	auto amountOfLines = LineCounter::getAmountOfLines("C:/Users/micha/Desktop/cpp/SFML/RPG/RPG");
	std::cout <<"Amount of lines in project = "<< amountOfLines << std::endl;
	getchar();
	return 0;
}
