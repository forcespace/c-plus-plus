#pragma once

class CPoint
{
public:
	CPoint(double x, double y);

	bool static Equal(const CPoint& firstPoint, const CPoint& secondPoint);

	double x;
	double y;
};
