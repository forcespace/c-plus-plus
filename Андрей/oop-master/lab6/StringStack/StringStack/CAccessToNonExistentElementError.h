#pragma once
#include <stdexcept>

class CAccessToNonExistentElementError : public std::runtime_error
{
public:
	CAccessToNonExistentElementError(const std::string& message);
};
