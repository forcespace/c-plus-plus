#pragma once
#include "ICanvas.h"
#include <SFML/Graphics.hpp>

class CCanvas 
	: public ICanvas
{
public:
	CCanvas(sf::RenderWindow& window);
	void DrawLine(CPoint const& startPoint, CPoint const& endPoint, uint32_t const& color) const override;
	void DrawFillPoligon(std::vector<CPoint> const& points, uint32_t const& fillColor, uint32_t const& outlineColor) const override;
	void DrawFillCircle(CPoint const& centerPoint, double const& radius, uint32_t const& fillColor, uint32_t const& outlineColor) const override;

private:
	sf::RenderWindow& m_window;
	sf::Color GetRGB(uint32_t const& color) const;
};

