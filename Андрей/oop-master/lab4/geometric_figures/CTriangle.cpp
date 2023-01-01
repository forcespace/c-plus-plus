#include "CTriangle.h"
#include "CPoint.h"
#include "CLineSegment.h"
#include "common_libs.h"

CTriangle::CTriangle(const CPoint& firstVertex, const CPoint& secondVertex, const CPoint& thirdVertex, const uint32_t outlineColor, const uint32_t fillColor)
	: CSolidShape(fillColor, outlineColor)
	, m_firstVertex(firstVertex)
	, m_secondVertex(secondVertex)
	, m_thirdVertex(thirdVertex)
{
}

double CTriangle::GetArea() const
{
	return 0.5 * abs((m_secondVertex.x - m_firstVertex.x) * (m_thirdVertex.y - m_firstVertex.y) 
		- (m_thirdVertex.x - m_firstVertex.x) * (m_secondVertex.y - m_firstVertex.y));
}

CPoint CTriangle::GetVertex1() const
{
	return m_firstVertex;
}

CPoint CTriangle::GetVertex2() const
{
	return m_secondVertex;
}

CPoint CTriangle::GetVertex3() const
{
	return m_thirdVertex;
}

std::string CTriangle::ToString() const
{
	std::ostringstream oss;

	oss << std::fixed << std::setprecision(1)
		<< "triangle with points "
		<< "(" << m_firstVertex.x << ", " << m_firstVertex.y << "), "
		<< "(" << m_secondVertex.x << ", " << m_secondVertex.y << "), "
		<< "(" << m_thirdVertex.x << ", " << m_thirdVertex.y << "), "
		<< "outline color: #" << std::hex << GetOutlineColor() << " and fill color: #" << std::hex << GetFillColor();

	return oss.str();
}

void CTriangle::Draw(ICanvas& canvas) const
{
	std::vector<CPoint> points = {
		m_firstVertex,
		m_secondVertex,
		m_thirdVertex,
	};

	canvas.DrawPolygon(points, GetOutlineColor(), GetFillColor());
}

double GetLenght(CPoint firstPoint, CPoint secondPoint)
{
	return sqrt(pow((firstPoint.x - secondPoint.x), 2) + pow((firstPoint.y - secondPoint.y), 2));
}

double CTriangle::GetPerimeter() const
{
	return GetLenght(m_firstVertex, m_secondVertex) + GetLenght(m_secondVertex, m_thirdVertex) + GetLenght(m_thirdVertex, m_firstVertex);
}