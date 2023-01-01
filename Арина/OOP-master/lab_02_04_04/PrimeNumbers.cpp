#include "PrimeNumbers.h"

std::optional<Args> GetNumberFromInput(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Invalid arguments count." << std::endl;
		std::cout << "Usage: lab_02_04_04.exe <your number>." << std::endl;
		return std::nullopt;
	}
	Args number;
	try
	{
		number.value = std::stoul(argv[1]);
		return number;
	}
	catch (const std::exception&)
	{
		return std::nullopt;
	}
}

std::vector<bool> GeneratePrimeNumbersGrid(unsigned int upperBound)
{
	std::vector<bool> prime(size_t(upperBound + 1), true);
	prime[0] = prime[1] = false;
	for (unsigned int i = 2; i * i <= upperBound; ++i)
		if (prime[i])
			for (unsigned int j = i * i; j <= upperBound; j += i)
				prime[j] = false;
	return prime;
}

std::set<int> GeneratePrimeNumbersSet(unsigned int upperBound)
{
	const unsigned int MAX_UPPER_BOUND = 100000000;
	std::set<int> set;
	if (upperBound < 0 || upperBound > MAX_UPPER_BOUND)
	{
		std::cout << "Entered value is out of range." << std::endl;
		return set;
	}
	auto prime = GeneratePrimeNumbersGrid(upperBound);
	for (int i = 0; i < int(prime.size()); i++)
		if (prime[i])
			set.insert(i);
	return set;
}