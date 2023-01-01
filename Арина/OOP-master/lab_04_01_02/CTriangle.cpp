#include "CTriangle.h"
#include <iostream>
#include <sstream>

CTriangle::CTriangle(CPoint const& vertex1, CPoint const& vertex2, CPoint const& vertex3, std::string const& fillColor, std::string const& outlineColor)
	: m_vertex1(vertex1)
	, m_vertex2(vertex2)
	, m_vertex3(vertex3)
{
	SetFillColor(stoul(fillColor, nullptr, 16));
	SetOutlineColor(stoul(outlineColor, nullptr, 16));
}

double CTriangle::GetArea() const
{
	double halfPerimeter = GetPerimeter() / 2;
	const CPoint vertex1 = GetVertex1();
	const CPoint vertex2 = GetVertex2();
	const CPoint vertex3 = GetVertex3();

	return sqrt(
		halfPerimeter 
		* (halfPerimeter - hypot(vertex2.x() - vertex1.x(), vertex2.y() - vertex1.y()))
		* (halfPerimeter - hypot(vertex3.x() - vertex2.x(), vertex3.y() - vertex2.y()))
		* (halfPerimeter - hypot(vertex3.x() - vertex1.x(), vertex3.y() - vertex1.y()))
	);
}

double CTriangle::GetPerimeter() const
{
	const CPoint vertex1 = GetVertex1();
	const CPoint vertex2 = GetVertex2();
	const CPoint vertex3 = GetVertex3();

	return hypot(vertex2.x() - vertex1.x(), vertex2.y() - vertex1.y())
		+ hypot(vertex3.x() - vertex2.x(), vertex3.y() - vertex2.y())
		+ hypot(vertex3.x() - vertex1.x(), vertex3.y() - vertex1.y());
}

std::string CTriangle::ToString() const
{
	std::stringstream str;
	const CPoint vertex1 = GetVertex1();
	const CPoint vertex2 = GetVertex2();
	const CPoint vertex3 = GetVertex3();

	str << "  Name: Triangle" << std::endl
		<< "  Vertex 1: (" << vertex1.x() << ", " << vertex1.y() << ")" << std::endl
		<< "  Vertex 2: (" << vertex2.x() << ", " << vertex2.y() << ")" << std::endl
		<< "  Vertex 3: (" << vertex3.x() << ", " << vertex3.y() << ")" << std::endl
		<< "  Area: " << GetArea() << std::endl
		<< "  Perimeter: " << GetPerimeter() << std::endl
		<< "  Fill color: " << std::hex << "0x" << GetFillColor() << std::endl
		<< "  Outline color: " << std::hex << "0x" << GetOutlineColor() << std::endl;

	return str.str();
}

void CTriangle::Draw(ICanvas& canvas) const
{
	std::vector<CPoint> points = {
		   { m_vertex1.x(), m_vertex1.y() },
		   { m_vertex2.x(), m_vertex2.y() },
		   { m_vertex3.x(), m_vertex3.y() }
	};
	canvas.DrawFillPoligon(points, GetFillColor(), GetOutlineColor());
}

CPoint CTriangle::GetVertex1() const
{
	return m_vertex1;
}

CPoint CTriangle::GetVertex2() const
{
	return m_vertex2;
}

CPoint CTriangle::GetVertex3() const
{
	return m_vertex3;
}
