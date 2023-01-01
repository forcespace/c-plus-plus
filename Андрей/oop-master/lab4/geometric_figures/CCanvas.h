#pragma once
#include "ICanvas.h"
#include <SFML/Graphics.hpp>

class CCanvas : public ICanvas
{
public:
	CCanvas(sf::RenderWindow& window);

	void DrawLine(const CPoint& firstPoint, const CPoint& secondPoint, uint32_t outlineColor) override;

	void DrawPolygon(const std::vector<CPoint>& points, uint32_t outlineColor, uint32_t fillColor) override;

	void DrawCircle(const CPoint& center, double radius, uint32_t outlineColor, uint32_t fillColor) override;

private:
	sf::RenderWindow& m_window;

	int m_width;
	int m_height;
};
