#include "CEmptyStackError.h"

CEmptyStackError::CEmptyStackError(const std::string& message)
	: std::logic_error(message)
{
}