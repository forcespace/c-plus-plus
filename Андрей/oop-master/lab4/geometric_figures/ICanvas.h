#pragma once
#include "CPoint.h"
#include <vector>

class ICanvas
{
public:
	virtual ~ICanvas() = default;

	virtual void DrawLine(const CPoint& firstPoint, const CPoint& secondPoint, uint32_t outlineColor) = 0;

	virtual void DrawPolygon(const std::vector<CPoint>& points, uint32_t outlineColor, uint32_t fillColor) = 0;

	virtual void DrawCircle(const CPoint& center, double radius, uint32_t outlineColor, uint32_t fillColor) = 0;
};