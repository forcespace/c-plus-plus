#include "CShape.h"

void CShape::SetOutlineColor(uint32_t const& color)
{
	m_outlineColor = color;
}

uint32_t CShape::GetOutlineColor() const
{
	return m_outlineColor;
}
