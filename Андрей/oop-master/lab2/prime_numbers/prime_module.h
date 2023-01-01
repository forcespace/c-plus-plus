#pragma once

#include <iostream>
#include <optional>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>
#include <cmath>

std::set<int> GetPrimeNumbers(const int upperBound);
void WriteSet(std::ostream& outFile, std::set<int> primeNumbersSet);