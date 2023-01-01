#include "UnableChangeIteratorError.h"

UnableChangeIteratorError::UnableChangeIteratorError(const std::string& message)
	: std::logic_error(message)
{
};