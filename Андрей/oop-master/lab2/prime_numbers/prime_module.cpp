#include "prime_module.h"

std::set<int> GetPrimeNumbers(const int upperBound)
{
	std::set<int> primeNumbers;

	if (upperBound < 2)
	{
		return primeNumbers;
	}

	std::vector<bool> sieve(upperBound + 1, true);

	primeNumbers.insert(2);

	for (auto index = 3; index < upperBound + 1; index += 2)
	{
		if (sieve[index])
		{
			primeNumbers.insert(primeNumbers.end(), index);
			
			if (index < sqrt(upperBound - 1))
			{
				for (auto i = index * index; i < upperBound + 1; i += index)
				{
					sieve[i] = false;
				}
			}
		}
	}

	return primeNumbers;
}

void WriteSet(std::ostream& outFile, std::set<int> primeNumbersSet)
{
	for (auto element : primeNumbersSet)
	{
		outFile << element << " ";
	}
}