#pragma once

#include <algorithm>
#include <codecvt>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <locale>
#include <optional>
#include <set>
#include <sstream>
#include <string>

std::optional<std::set<std::string>> GetSetFromString(const std::string_view& line, const std::string& separator);

std::string GetStringInLowerCase(const std::string& line);
