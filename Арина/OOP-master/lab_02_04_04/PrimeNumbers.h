#pragma once
#include <optional>
#include <iostream>
#include <string>
#include <set>
#include <vector>

struct Args
{
	unsigned int value;
};

std::optional<Args> GetNumberFromInput(int argc, char* argv[]);
std::vector<bool> GeneratePrimeNumbersGrid(unsigned int upperBound);
std::set<int> GeneratePrimeNumbersSet(unsigned int upperBound);

