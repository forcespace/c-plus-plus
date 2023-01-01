#pragma once
#include "ISolidShape.h"

class CSolidShape : public ISolidShape
{
public:
	CSolidShape(const uint32_t fillColor, const uint32_t outlineColor);

	virtual ~CSolidShape() = default;

	uint32_t GetFillColor() const override final;

	uint32_t GetOutlineColor() const override final;

protected:
	virtual double GetArea() const
	{
		throw std::runtime_error("Error, can't get area of this shape");
	}

	virtual double GetPerimeter() const
	{
		throw std::runtime_error("Error, can't get perimeter of this shape");
	}

	virtual std::string ToString() const
	{
		throw std::runtime_error("Error, can't covert this shape to string");
	}

private:

	uint32_t m_fillColor;
	
	uint32_t m_outlineColor;
};
