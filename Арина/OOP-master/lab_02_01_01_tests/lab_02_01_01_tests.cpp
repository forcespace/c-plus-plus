#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>
#include "../lab_02_01_01/ProcessVector.h"

SCENARIO("Processing of empty vector gives empty vector")
{
	std::vector<double> v = { };
	std::vector<double> result = { };
	ProcessVector(v);
	CHECK(v == result);
}

SCENARIO("Processing of vector with one element gives vector with one element")
{
	std::vector<double> v = { 1.222 };
	std::vector<double> result = { 2.444 };
	ProcessVector(v);
	CHECK(v == result);
}

SCENARIO("Processing of vector with multiple elements gives vector with multiple elements")
{
	std::vector<double> v = { 1.222, 2.444, 3.222 };
	std::vector<double> result = { 3.518, 4.74, 5.518 };
	ProcessVector(v);
	CHECK(v.size() == result.size());
	CHECK(v == result);
}

SCENARIO("Processing of vector with negative number gives vector with negative number")
{
	std::vector<double> v = { 0.0, -1.222 };
	std::vector<double> result = { 0.0, -1.222 };
	ProcessVector(v);
	CHECK(v.size() == result.size());
	CHECK(v == result);
}