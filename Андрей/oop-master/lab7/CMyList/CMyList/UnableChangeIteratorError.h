#pragma once
#include <stdexcept>

class UnableChangeIteratorError : public std::logic_error
{
public:
	UnableChangeIteratorError(const std::string& message);
};
