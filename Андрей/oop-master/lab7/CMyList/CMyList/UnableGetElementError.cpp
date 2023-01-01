#include "UnableGetElementError.h"

UnableGetElementError::UnableGetElementError(const std::string& message)
	: std::runtime_error(message)
{
}
