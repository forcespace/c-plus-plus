#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../find_max_ex/find_max.h"
#include "../find_max_ex/sportsman_module.h"

TEST_CASE("Test with error")
{
	GIVEN("max = 1; vector = {}")
	{
		int max = 1;
		std::vector<int> vector = {};

		WHEN("find max")
		{
			bool result = FindMaxEx(vector, max, [](int a, int b) { return a < b; });

			THEN("max = 5")
			{
				REQUIRE_FALSE(result);
				REQUIRE(max == 1);
			}
		}
	}
}

TEST_CASE("Test functional")
{
	GIVEN("max = 1; vector = {1}")
	{
		int max = 3;

		WHEN("find max")
		{
			bool result = FindMaxEx(std::vector{ 1 }, max, [](int a, int b) { return a < b; });

			THEN("max = 1")
			{
				REQUIRE(result);
				REQUIRE(max == 1);
			}
		}
	}

	GIVEN("max = 1; vector = {1, 2, 3, 5, 1}")
	{
		int max = 1;

		WHEN("find max")
		{
			bool result = FindMaxEx(std::vector{ 1, 2, 3, 5, 1 }, max, [](int a, int b) { return a < b; });

			THEN("max = 5")
			{
				REQUIRE(result);
				REQUIRE(max == 5);
			}
		}
	}

	GIVEN("max = 1.2; vector = {1.2, 2.93, 3.1, 5.321, 1.12, 5.322}")
	{
		double max = 1.2;

		WHEN("find max")
		{
			bool result = FindMaxEx(std::vector{ 1.2, 2.93, 3.1, 5.321, 1.12, 5.322 }, max, [](double a, double b) { return a < b; });

			THEN("max = 5.322")
			{
				REQUIRE(result);
				REQUIRE(max == 5.322);
			}
		}
	}

	GIVEN("max = 'a'; vector = {'a', 'b', 'e', 'z', 'y', 'x'}")
	{
		char max = 'a';
		
		WHEN("find max")
		{
			bool result = FindMaxEx(std::vector{ 'a', 'b', 'e', 'z', 'y', 'x' }, max, [](char a, char b) { return a < b; });

			THEN("max = 'z'")
			{
				REQUIRE(result);
				REQUIRE(max == 'z');
			}
		}
	}

	GIVEN("max = 'a'; vector = {'a', 'b', 'e', 'z', 'y', 'x'}")
	{
		char max = 'a';

		WHEN("find max")
		{
			bool result = FindMaxEx(std::vector{ 'a', 'b', 'e', 'z', 'y', 'x' }, max, [](char a, char b) { return a < b; });

			THEN("max = 'z'")
			{
				REQUIRE(result);
				REQUIRE(max == 'z');
			}
		}
	}

	GIVEN("sportsmen")
	{
		std::vector<Sportsman> sportsmen = {
			{ "Karanbek Abdul", 170.1, 90.5 },
			{ "Daxadaev Mahach", 164.3, 54.4 },
			{ "Aleev Muhu", 201.5, 106.0 },
			{ "Daklunbek Ulug", 183.6, 86.7 },
			{ "Zuravelbek Abuldaren", 183.6, 120.9 }
		};

		WHEN("find max")
		{
			Sportsman tallestSportsman;
			Sportsman heaviestSportsman;

			bool tallestSportsmanResult = FindMaxEx(sportsmen, tallestSportsman, [](Sportsman first, Sportsman second) { return first.height < second.height; });
			bool heaviestSportsmanResult = FindMaxEx(sportsmen, heaviestSportsman, [](Sportsman first, Sportsman second) { return first.weight < second.weight; });

			THEN("the tallest = 'Aleev Muhu'")
			{
				REQUIRE(tallestSportsmanResult);
				REQUIRE(tallestSportsman.name == "Aleev Muhu");
				REQUIRE(tallestSportsman.height == 201.5);
				REQUIRE(tallestSportsman.weight == 106.0);
			}

			THEN("the heaviest = 'Zuravelbek Abuldaren'")
			{
				REQUIRE(heaviestSportsmanResult);
				REQUIRE(heaviestSportsman.name == "Zuravelbek Abuldaren");
				REQUIRE(heaviestSportsman.height == 183.6);
				REQUIRE(heaviestSportsman.weight == 120.9);
			}
		}
	}
}
