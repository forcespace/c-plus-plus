#pragma once
#include "CPoint.h"
#include "CSolidShape.h"

class CRectangle :
	public CSolidShape
{
public:
	CRectangle(CPoint const& leftTopPoint, double const& width, double const& height, std::string const& fillColor, std::string const& outlineColor);

	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	void Draw(ICanvas& canvas) const override;

	CPoint GetLeftTopPoint() const;
	CPoint GetRightBottomPoint() const;
	double GetWidth() const;
	double GetHeight() const;

private:
	CPoint m_leftTopPoint = CPoint(0, 0);
	double m_width = 0;
	double m_height = 0;
};

