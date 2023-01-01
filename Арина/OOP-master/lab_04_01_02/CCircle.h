#pragma once
#include "CPoint.h"
#include "CSolidShape.h"

class CCircle :
	public CSolidShape
{
public:
	CCircle(CPoint const& centerPoint, double const& radius, std::string const& fillColor, std::string const& outlineColor);

	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	void Draw(ICanvas& canvas) const override;

	CPoint GetCenter() const;
	double GetRadius() const;

private:
	CPoint m_center = CPoint(0, 0);
	double m_radius = 0;
};

