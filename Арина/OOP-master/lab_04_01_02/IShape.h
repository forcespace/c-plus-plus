#pragma once
#include "ICanvasDrawable.h"
#include <string>

class IShape :
	virtual public ICanvasDrawable
{
public:
	virtual double GetArea() const = 0;
	virtual double GetPerimeter() const = 0;
	virtual std::string ToString() const = 0;
	virtual uint32_t GetOutlineColor() const = 0;
	virtual void SetOutlineColor(uint32_t const& color) = 0;
};