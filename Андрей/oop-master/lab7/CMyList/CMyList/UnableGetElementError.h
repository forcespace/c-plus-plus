#pragma once
#include <stdexcept>

class UnableGetElementError : public std::runtime_error
{
public:
	UnableGetElementError(const std::string& message);
};
