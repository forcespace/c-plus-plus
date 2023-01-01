#include "CAccessToNonExistentElementError.h"

CAccessToNonExistentElementError::CAccessToNonExistentElementError(const std::string& message)
	: std::runtime_error(message)
{
}