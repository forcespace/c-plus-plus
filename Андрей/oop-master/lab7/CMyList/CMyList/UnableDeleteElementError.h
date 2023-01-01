#pragma once
#include <stdexcept>

class UnableDeleteElementError : public std::logic_error
{
public:
	UnableDeleteElementError(const std::string& message);
};
