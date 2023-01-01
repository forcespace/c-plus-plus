#pragma once
#include "CShape.h"
#include "CPoint.h"

class CLineSegment :
	public CShape
{
public:
	CLineSegment(CPoint const& startPoint, CPoint const& endPoint, std::string const& outlineColor);

	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	void Draw(ICanvas& canvas) const override;

	CPoint GetStartPoint() const;
	CPoint GetEndPoint() const;

private:
	CPoint m_startPoint = CPoint(0, 0);
	CPoint m_endPoint = CPoint(0, 0);
};

