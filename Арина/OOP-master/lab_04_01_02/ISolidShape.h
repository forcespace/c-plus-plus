#pragma once
#include "IShape.h"

class ISolidShape :
	virtual public IShape
{
public:
	virtual ~ISolidShape() = default;

	virtual void SetFillColor(uint32_t const& color) = 0;
	virtual uint32_t GetFillColor() const = 0;
};