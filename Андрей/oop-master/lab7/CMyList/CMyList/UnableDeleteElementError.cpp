#include "UnableDeleteElementError.h"

UnableDeleteElementError::UnableDeleteElementError(const std::string& message)
	: std::logic_error(message)
{
};
