#include <algorithm>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <numeric>
#include <optional>
#include <vector>

#include "vector_functions.h"

void ReadAndSplitArrayElementsByHalfOfMaximumElement(std::istream& inFile, std::ostream& outFile)
{
	auto numbers = ReadNumbers(inFile);

	if (!numbers.has_value())
	{
		throw std::invalid_argument("Wrong input of numbers.");
	}

	DivideArrayElementsByHalfOfMaximumElement(numbers.value());

	std::sort(numbers.value().begin(), numbers.value().end());
	OutputNumbers(outFile, numbers.value());
}

std::optional<std::vector<double>> ReadNumbers(std::istream& inFile)
{
	std::vector<double> vector;

	double number;

	while (inFile >> number)
	{
		vector.push_back(number);
	}

	if (!inFile.eof() || inFile.bad())
	{
		return std::nullopt;
	}

	return { vector };
}

void OutputNumbers(std::ostream& outFile, const std::vector<double>& vector)
{
	for (auto const& element : vector)
	{
		outFile << std::fixed << std::setprecision(3) << element << " ";
	}

	outFile << std::endl;
}

void DivideArrayElementsByHalfOfMaximumElement(std::vector<double>& vector)
{
	if (!vector.size())
	{
		return;
	}

	double maxElement = *std::max_element(vector.begin(), vector.end());

	std::transform(vector.begin(), vector.end(), vector.begin(), [maxElement](const double element) { return element * 2 / maxElement; });
}
