#include "CSolidShape.h"

void CSolidShape::SetFillColor(uint32_t const& color)
{
	m_fillColor = color;
}

uint32_t CSolidShape::GetFillColor() const
{
	return m_fillColor;
}

void CSolidShape::SetOutlineColor(uint32_t const& color)
{
	CShape::SetOutlineColor(color);
}

uint32_t CSolidShape::GetOutlineColor() const
{
	return CShape::GetOutlineColor();
}
