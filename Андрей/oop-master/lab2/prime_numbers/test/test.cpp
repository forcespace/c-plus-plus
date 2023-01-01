#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../prime_module.h"

TEST_CASE("Check limit values")
{
	REQUIRE(GetPrimeNumbers(0).empty());
	REQUIRE(GetPrimeNumbers(1).empty());
	REQUIRE(GetPrimeNumbers(2) == std::set<int>{2});
	REQUIRE(GetPrimeNumbers(3) == std::set<int>{2, 3});
	REQUIRE(GetPrimeNumbers(-1).empty());
	REQUIRE(GetPrimeNumbers(-10).empty());
}

TEST_CASE("Check usual values")
{
	REQUIRE(GetPrimeNumbers(150).size() == 35);
	REQUIRE(GetPrimeNumbers(151).size() == 36);

	#ifndef _DEBUG
		REQUIRE(GetPrimeNumbers(100000000).size() == 5761455);
	#endif // DEBUG
}