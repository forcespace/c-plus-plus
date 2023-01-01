#include "CLineSegment.h"
#include "CPoint.h"
#include "CShape.h"
#include "common_libs.h"

CLineSegment::CLineSegment(const CPoint& startPoint, const CPoint& endPoint, const uint32_t outlineColor) 
	: CShape(outlineColor) 
	, m_startPoint(startPoint)
	, m_endPoint(endPoint)
{
}

double CLineSegment::GetArea() const
{
	return 0;
}

double CLineSegment::GetPerimeter() const
{
	return sqrt(pow(m_startPoint.y - m_endPoint.y, 2) + pow(m_startPoint.x - m_endPoint.x, 2));
}

std::string CLineSegment::ToString() const
{
	std::ostringstream oss;

	oss << std::fixed << std::setprecision(1)
		<< "line with points "
		<< "(" << m_startPoint.x << ", " << m_startPoint.y << "), "
		<< "(" << m_endPoint.x << ", " << m_endPoint.y << "), "
		<< "outline color: #" << std::hex << GetOutlineColor();

	return oss.str();
}

void CLineSegment::Draw(ICanvas& canvas) const
{
	canvas.DrawLine(m_startPoint, m_endPoint, GetOutlineColor());
}

CPoint CLineSegment::GetStartPoint() const
{
	return m_startPoint;
}

CPoint CLineSegment::GetEndPoint() const
{
	return m_endPoint;
}
