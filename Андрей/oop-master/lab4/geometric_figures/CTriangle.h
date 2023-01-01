#pragma once
#include "CPoint.h"
#include "CSolidShape.h"
#include "common_libs.h"

class CTriangle : public CSolidShape
{
public:
	CTriangle(const CPoint& firstVertex, const CPoint& secondVertex, const CPoint& thirdVertex, const uint32_t outlineColor, const uint32_t fillColor);

	double GetArea() const override;

	double GetPerimeter() const override;

	std::string ToString() const override;

	void Draw(ICanvas& canvas) const override;

	CPoint GetVertex1() const;

	CPoint GetVertex2() const;

	CPoint GetVertex3() const;

private:
	CPoint m_firstVertex;

	CPoint m_secondVertex;

	CPoint m_thirdVertex;
};
