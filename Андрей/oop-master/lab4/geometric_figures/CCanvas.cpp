#include "CCanvas.h"

CCanvas::CCanvas(sf::RenderWindow& window)
	: m_window(window)
	, m_width(window.getSize().x)
	, m_height(window.getSize().y)
{
}

sf::Color GetColor(uint32_t color)
{
	uint32_t blue = color % 256;
	uint32_t green = (color / 256) % 256;
	uint32_t red = ((color / 256) / 256) % 256;

	return sf::Color(red, green, blue);
}

void CCanvas::DrawLine(const CPoint& firstPoint, const CPoint& secondPoint, uint32_t outlineColor)
{
	sf::Vertex line[2] = {
		sf::Vector2f((float)firstPoint.x, (float)firstPoint.y),
		sf::Vector2f((float)secondPoint.x, (float)secondPoint.y),
	};

	line[0].color = GetColor(outlineColor);
	line[1].color = GetColor(outlineColor);

	m_window.draw(line, 2, sf::Lines);
}

void CCanvas::DrawPolygon(const std::vector<CPoint>& points, uint32_t outlineColor, uint32_t fillColor)
{
	sf::ConvexShape shape;
	shape.setPointCount(points.size());

	for (size_t i = 0; i < points.size(); i++)
	{
		shape.setPoint(i, sf::Vector2f((float)points[i].x, (float)points[i].y));
	}

	shape.setFillColor(GetColor(fillColor));
	shape.setOutlineColor(GetColor(fillColor));

	m_window.draw(shape);
}

void CCanvas::DrawCircle(const CPoint& center, double radius, uint32_t outlineColor, uint32_t fillColor)
{
	sf::CircleShape shape;

	shape.move(sf::Vector2f((float)center.x, (float)center.y));
	shape.setOrigin((float)radius, (float)radius);
	shape.setRadius((float)radius);

	shape.setFillColor(GetColor(fillColor));
	shape.setOutlineColor(GetColor(fillColor));

	m_window.draw(shape);
}
