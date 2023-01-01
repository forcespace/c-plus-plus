#include "CSession.h"
#include "CCanvas.h"

const std::map <std::string, std::pair<Shapes, int>> commandMap = {
	{ "circle",      { Shapes::Circle,      6 } },
	{ "linesegment", { Shapes::LineSegment, 6 } },
	{ "rectangle",   { Shapes::Rectangle,   7 } },
	{ "triangle",    { Shapes::Triangle,    9 } },
};

void CSession::ProcessCommand(std::istream& commands)
{
	std::string line;
	std::vector<std::string> command;

	while (std::getline(commands, line))
	{
		boost::algorithm::to_lower(line);
		boost::split(command, line, [](char c) {return c == ' '; });
		if (command[0] == "") continue;
		if (command[0] == EXIT_TEXT) break;
		auto it = commandMap.find(command[0]);
		if (it->second.second == command.size())
		{
			CSession::CreateShape(it->second.first, command);
		}
		else
		{
			throw std::invalid_argument("Invalid count of arguments.");
		}
	}
}

std::vector<std::unique_ptr<IShape>>::const_iterator CSession::GetMaxAriaShape() const
{
	if (m_shapes.empty())
		return m_shapes.end();

	return std::max_element(m_shapes.cbegin(), m_shapes.cend(), [](auto& lhs, auto& rhs) {
		return lhs->GetArea() < rhs->GetArea();
	});
}

std::vector<std::unique_ptr<IShape>>::const_iterator CSession::GetMinPerimeterShape() const
{
	if (m_shapes.empty())
		return m_shapes.end();

	return std::min_element(m_shapes.cbegin(), m_shapes.cend(), [](auto& lhs, auto& rhs) {
		return lhs->GetPerimeter() < rhs->GetPerimeter();
	});
}

std::string CSession::GetShapeInfo(std::vector<std::unique_ptr<IShape>>::const_iterator shape) const
{
	return (shape != m_shapes.end()) ? (*shape)->ToString() : "";
}

void CSession::DrawShapes() const
{
	if (!m_shapes.empty())
	{
		sf::RenderWindow window(sf::VideoMode(800, 800), "Draw Shapes");
		CCanvas canvas(window);
		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
				if (event.type == sf::Event::Closed)
					window.close();

			window.clear(sf::Color::White);

			for (const auto& shape : m_shapes)
				shape->Draw(canvas);

			window.display();
		}
	}
}

void CSession::CreateShape(Shapes shape, std::vector<std::string> command)
{
	switch (shape)
	{
	case Shapes::Circle:
	{
		CSession::CreateCircle(command);
		break;
	}
	case Shapes::LineSegment:
	{
		CSession::CreateLineSegment(command);
		break;
	}
	case Shapes::Rectangle:
	{
		CSession::CreateRectangle(command);
		break;
	}
	case Shapes::Triangle:
	{
		CSession::CreateTriangle(command);
		break;
	}
	default:
	{
		throw std::invalid_argument("Unknow command.");
		break;
	}
	}
}

void CSession::CreateCircle(std::vector<std::string> command)
{
	try
	{
		return m_shapes.push_back(std::make_unique<CCircle>(
			CPoint(stod(command[1]), stod(command[2])), 
			stod(command[3]), 
			command[4], 
			command[5]
		));
	}
	catch (const std::logic_error&)
	{
		throw std::invalid_argument("Invalid argument for Circle.");
	}
}

void CSession::CreateLineSegment(std::vector<std::string> command)
{
	try
	{
		return m_shapes.push_back(std::make_unique<CLineSegment>(
			CPoint(stod(command[1]), stod(command[2])), 
			CPoint(stod(command[3]), stod(command[4])), 
			command[5]
		));
	}
	catch (const std::logic_error&)
	{
		throw std::invalid_argument("Invalid argument for Line Segment.");
	}
}

void CSession::CreateRectangle(std::vector<std::string> command)
{
	try
	{
		return m_shapes.push_back(std::make_unique<CRectangle>(
			CPoint(stod(command[1]), stod(command[2])), 
			stod(command[3]), 
			stod(command[4]), 
			command[5], 
			command[6]
		));
	}
	catch (const std::logic_error&)
	{
		throw std::invalid_argument("Invalid argument for Rectangle.");
	}
}

void CSession::CreateTriangle(std::vector<std::string> command)
{
	try
	{
		return m_shapes.push_back(std::make_unique<CTriangle>(
			CPoint(stod(command[1]), stod(command[2])), 
			CPoint(stod(command[3]), stod(command[4])), 
			CPoint(stod(command[5]), stod(command[6])), 
			command[7], 
			command[8]
		));
	}
	catch (const std::logic_error&)
	{
		throw std::invalid_argument("Invalid argument for Triangle.");
	}
}