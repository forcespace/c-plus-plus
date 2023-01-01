#pragma once
#include "CPoint.h"
#include "CSolidShape.h"
#include "common_libs.h"

class CRectangle : public CSolidShape
{
public:
	CRectangle(const CPoint& topLeftPoint, const double width, const double height, const uint32_t outlineColor, const uint32_t fillColor);
	
	double GetArea() const override;

	double GetPerimeter() const override;

	std::string ToString() const override;

	void Draw(ICanvas& canvas) const override;

	CPoint GetTopLeftPoint() const;
	
	CPoint GetBottomRightPoint() const;
	
	double GetWidth() const;
	
	double GetHeight() const;

private:
	CPoint m_topLeftPoint;

	double m_width;

	double m_height;
};
