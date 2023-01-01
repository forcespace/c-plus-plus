#include <iostream>
#include <optional>
#include <vector>

std::optional<std::vector<double>> ReadNumbers(std::istream& inFile);

void ReadAndSplitArrayElementsByHalfOfMaximumElement(std::istream& inFile, std::ostream& outFile);

void OutputNumbers(std::ostream& outFile, const std::vector<double>& vector);

void DivideArrayElementsByHalfOfMaximumElement(std::vector<double>& vector);
