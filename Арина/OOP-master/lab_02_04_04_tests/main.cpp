#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>

#include "../lab_02_04_04/PrimeNumbers.h"

SCENARIO("Generate prime numbers.")
{
	auto primes = GeneratePrimeNumbersSet(0);
	CHECK(primes.size() == 0);

	primes = GeneratePrimeNumbersSet(10);
	CHECK(primes.size() == 4);	

	primes = GeneratePrimeNumbersSet(100000000);
	CHECK(primes.size() == 5761455);
}

SCENARIO("Generate prime numbers (invalid upper bound).")
{
	auto primes = GeneratePrimeNumbersSet(100000001);
	CHECK(primes.size() == 0);

	primes = GeneratePrimeNumbersSet(-1);
	CHECK(primes.size() == 0);
}