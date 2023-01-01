#include "CCanvas.h"

CCanvas::CCanvas(sf::RenderWindow& window)
	: m_window(window)
{
}

void CCanvas::DrawLine(CPoint const& startPoint, CPoint const& endPoint, uint32_t const& color) const
{
	sf::Vertex line[] =
	{
		sf::Vertex(sf::Vector2f(startPoint.x(), startPoint.y())),
		sf::Vertex(sf::Vector2f(endPoint.x(), endPoint.y()))
	};
	line[0].color = GetRGB(color);
	line[1].color = GetRGB(color);
	m_window.draw(line, 2, sf::Lines);
}

void CCanvas::DrawFillPoligon(std::vector<CPoint> const& points, uint32_t const& fillColor, uint32_t const& outlineColor) const
{
	sf::ConvexShape polygon;
	polygon.setPointCount(points.size());
	for (size_t i = 0; i < points.size(); i++)
	{
		polygon.setPoint(i, sf::Vector2f(points[i].x(), points[i].y()));
	}
	polygon.setFillColor(GetRGB(fillColor));
	polygon.setOutlineColor(GetRGB(outlineColor));
	polygon.setOutlineThickness(1);
	m_window.draw(polygon);
}

void CCanvas::DrawFillCircle(CPoint const& centerPoint, double const& radius, uint32_t const& fillColor, uint32_t const& outlineColor) const
{
	sf::CircleShape circle;
	circle.setPosition(centerPoint.x() - radius, centerPoint.y() - radius);
	circle.setRadius(radius);
	circle.setFillColor(GetRGB(fillColor));
	circle.setOutlineColor(GetRGB(outlineColor));
	circle.setOutlineThickness(1);
	m_window.draw(circle);
}

sf::Color CCanvas::GetRGB(uint32_t const& color) const
{
	uint32_t red = ((color / 256) / 256) % 256;
	uint32_t green = (color / 256) % 256;
	uint32_t blue = color % 256;
	return sf::Color(red, green, blue);
}
