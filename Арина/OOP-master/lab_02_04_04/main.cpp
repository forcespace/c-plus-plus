#include "PrimeNumbers.h"
#include <algorithm>
#include <boost/timer.hpp>
#include <iostream>
#include <iterator>

int main(int argc, char* argv[])
{
	auto upperBound = GetNumberFromInput(argc, argv);
	if (!upperBound)
	{
		return 1;
	}

	std::cout << "Generating prime numbers from 1 to " << upperBound->value << '.' << std::endl;
	boost::timer t;
	t.restart();
	auto primeNumbers = GeneratePrimeNumbersSet(upperBound->value);
	double duration = t.elapsed();
	std::cout << "The time taken to get the set of prime numbers: " << duration << " sec." << std::endl;
	std::cout << "Count of prime numbers: " << primeNumbers.size() << '.' << std::endl;
	//std::copy(primeNumbers.begin(), primeNumbers.end(), std::ostream_iterator<unsigned int>(std::cout, " "));
	//std::cout << std::endl;
	return 0;
}