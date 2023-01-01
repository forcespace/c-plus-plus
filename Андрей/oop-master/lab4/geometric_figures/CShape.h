#pragma once
#include "IShape.h"

class CShape : public IShape
{
public:
	CShape(const uint32_t outlineColor);

	virtual ~CShape() = default;

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

	virtual void Draw(ICanvas& canvas) const override
	{
		throw std::runtime_error("Error, can't draw this shape");
	}

private:
	uint32_t m_outlineColor;
};
