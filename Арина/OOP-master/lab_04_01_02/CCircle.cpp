#include "CCircle.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <sstream>

CCircle::CCircle(CPoint const& centerPoint, double const& radius, std::string const& fillColor, std::string const& outlineColor)
	: m_center(centerPoint)
	, m_radius(radius)
{
	SetFillColor(stoul(fillColor, nullptr, 16));
	SetOutlineColor(stoul(outlineColor, nullptr, 16));
}

double CCircle::GetArea() const
{
	return M_PI * m_radius * m_radius;
}

double CCircle::GetPerimeter() const
{
	return 2 * M_PI * m_radius;
}

std::string CCircle::ToString() const
{
	std::stringstream str;
	const CPoint center = GetCenter();

	str << "  Name: Circle" << std::endl
		<< "  Center point: (" << center.x() << ", " << center.y() << ")" << std::endl
		<< "  Radius: " << GetRadius() << std::endl
		<< "  Area: " << GetArea() << std::endl
		<< "  Perimeter: " << GetPerimeter() << std::endl
		<< "  Fill color: " << std::hex << "0x" << GetFillColor() << std::endl
		<< "  Outline color: " << std::hex << "0x" << GetOutlineColor() << std::endl;

	return str.str();
}

void CCircle::Draw(ICanvas& canvas) const
{
	canvas.DrawFillCircle(m_center, m_radius, GetFillColor(), GetOutlineColor());
}

CPoint CCircle::GetCenter() const
{
	return m_center;
}

double CCircle::GetRadius() const
{
	return m_radius;
}
