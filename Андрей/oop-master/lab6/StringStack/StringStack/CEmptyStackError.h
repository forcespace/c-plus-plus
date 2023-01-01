#pragma once
#include <stdexcept>
#include <string>

class CEmptyStackError : std::logic_error
{
public:
	CEmptyStackError(const std::string& message);
};
