#include <iostream>
#include "ProcessVector.h"

int main(int argc, char *argv[])
{
    std::vector<double> numbers(std::istream_iterator<double>(std::cin), (std::istream_iterator<double>()));
    ProcessVector(numbers);
    std::sort(numbers.begin(), numbers.end());
    copy(numbers.begin(), numbers.end(), std::ostream_iterator<double>(std::cout, " "));

    return 0;
}