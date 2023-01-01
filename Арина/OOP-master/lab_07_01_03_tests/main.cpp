#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>
#include "../lab_07_01_03/FindMaxEx.h"

SCENARIO("Test FindMax")
{
	WHEN("Empty vector")
	{
		std::vector<int> vector;
		int maxValue;
		THEN("False")
		{
			CHECK_FALSE(FindMax(vector, maxValue, std::less<int>()));
		}
	}
	WHEN("Int Vector")
	{
		std::vector<int> vector = { 3, 1, 2 };
		int maxValue;
		THEN("True")
		{
			CHECK(FindMax(vector, maxValue, std::less<int>()));
			CHECK(maxValue == 3);
		}
	}
}

SCENARIO("Test Athletes")
{
	struct Athlete
	{
		std::string name;
		double height;
		double weight;
	};

	std::vector<Athlete> athletes = {
	{ "Steven", 175.3, 83 },
	{ "Maurice", 168.2, 72.6 },
	{ "Branden", 186.4, 84.8 },
	{ "Virgil", 171, 68.9 },
	{ "Robert", 179.6, 85.1 },
	};

	WHEN("Max height")
	{
		Athlete athlete;
		THEN("True")
		{
			CHECK(FindMax(athletes, athlete, [&](const Athlete& firstAthlete, const Athlete& secondAthlete) { 
				return firstAthlete.height < secondAthlete.height;
			}));
			CHECK(athlete.name == "Branden");
			CHECK(athlete.height == 186.4);
			CHECK(athlete.weight == 84.8);
		}
	}
	WHEN("Max weight")
	{
		Athlete athlete;
		THEN("True")
		{
			CHECK(FindMax(athletes, athlete, [&](const Athlete& firstAthlete, const Athlete& secondAthlete) {
				return firstAthlete.weight < secondAthlete.weight;
				}));
			CHECK(athlete.name == "Robert");
			CHECK(athlete.height == 179.6);
			CHECK(athlete.weight == 85.1);
		}
	}
}