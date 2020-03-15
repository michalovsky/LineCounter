#include "../Include/LineCounter.h"

int main()
{
    auto amountOfLines = LineCounter::getAmountOfLines("/home/michal/repos/glossary");
    std::cout << "Amount of lines in project = " << amountOfLines << std::endl;
    return 0;
}
