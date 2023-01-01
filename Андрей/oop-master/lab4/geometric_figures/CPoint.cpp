#include "CPoint.h"
#include "common_libs.h"

CPoint::CPoint(const double x, const double y)
	: x(x)
	, y(y)
{	
}

bool CPoint::Equal(const CPoint& firstPoint, const CPoint& secondPoint)
{
	return (firstPoint.x == secondPoint.x) && (firstPoint.y == secondPoint.y);
}