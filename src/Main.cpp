#include "LineCounter.h"

int main()
{
	auto amountOfLines = LineCounter::getAmountOfLines("/home/michal/repos/rpg");
	std::cout <<"Amount of lines in project = "<< amountOfLines << std::endl;
	return 0;
}
