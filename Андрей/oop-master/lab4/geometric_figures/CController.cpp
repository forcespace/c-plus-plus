#include "CController.h"
#include "CCanvas.h"
#include "CCircle.h"
#include "CLineSegment.h"
#include "CPoint.h"
#include "CRectangle.h"
#include "CTriangle.h"
#include "common_libs.h"

const std::map<std::string, std::string> regexForShapes = {
	{ "rectangle", "^([[:alpha:]]+) ([[:d:]]+(.[[:d:]]+)?) ([[:d:]]+(.[[:d:]]+)?) ([[:d:]]+(.[[:d:]]+)?) "
				   "([[:d:]]+(.[[:d:]]+)?) ([[:xdigit:]]{6}) ([[:xdigit:]]{6})$" },

	{ "line", "^([[:alpha:]]+) ([[:d:]]+(.[[:d:]]+)?) ([[:d:]]+(.[[:d:]]+)?) ([[:d:]]+(.[[:d:]]+)?)"
			  " ([[:d:]]+(.[[:d:]]+)?) ([[:xdigit:]]{6})$" },

	{ "circle", "^([[:alpha:]]+) ([[:d:]]+(.[[:d:]]+)?) ([[:d:]]+(.[[:d:]]+)?) ([[:d:]]+(.[[:d:]]+)?)"
				" ([[:xdigit:]]{6}) ([[:xdigit:]]{6})$" },

	{ "triangle", "^([[:alpha:]]+) ([[:d:]]+(.[[:d:]]+)?) ([[:d:]]+(.[[:d:]]+)?) ([[:d:]]+(.[[:d:]]+)?) "
				  "([[:d:]]+(.[[:d:]]+)?) ([[:d:]]+(.[[:d:]]+)?) ([[:d:]]+(.[[:d:]]+)?) ([[:xdigit:]]{6}) ([[:xdigit:]]{6})$" }
};

CController::CController(std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
	, m_actionMap({
		  { "rectangle", [this](const std::string& args) { return SetRectangle(args); } },
		  { "line", [this](const std::string& args) { return SetLine(args); } },
		  { "circle", [this](const std::string& args) { return SetCircle(args); } },
		  { "triangle", [this](const std::string& args) { return SetTriangle(args); } },
		  { "help", [this](const std::string& args) { return GetHelp(args); } },
	  })
{
}

void CController::GetShape() const
{
	std::string commandLine;
	std::getline(m_input, commandLine);

	std::istringstream stream(commandLine);

	std::string action;
	std::string args;
	std::getline(stream, action, ' ');
	args = std::getline(stream, args) ? args : "";

	auto it = m_actionMap.find(action);
	try
	{
		if (it != m_actionMap.end())
		{
			it->second(commandLine);
		}
	}
	catch (const std::exception& error)
	{
		throw std::invalid_argument(error.what());
	}
}

std::smatch CController::ParseString(const std::string& args) const
{
	std::stringstream iss(args);
	std::string shape;

	iss >> shape;

	std::smatch matches;

	auto it = regexForShapes.find(shape);
	if (it == regexForShapes.end())
	{
		throw std::invalid_argument("Error, wrong shape");
	}

	std::regex regex(it->second);

	regex_match(args, matches, regex);

	return matches;
}

void CController::WriteAllInfoAboutShapes() const
{
	if (m_shapesList.empty())
	{
		m_output << "There are no shapes" << std::endl;

		return;
	}

	WriteShapeWithMaxArea();
	WriteShapeWithMinPerimeter();
}

void CController::GetHelp(const std::string& args) const
{
	m_output << "line x1 y1 x2 y2 line color" << std::endl
			 << "rectangle x1 y1 width height outline color fill color" << std::endl
			 << "circle x1 y1 radius outline color fill color" << std::endl
			 << "triangle x1 y1 x2 y2 x3 y3 outline color fill color" << std::endl
			 << "Example: line 250 1 2 4 bbe4ff" << std::endl;
}

void CController::SetRectangle(const std::string& args)
{
	std::smatch matches = ParseString(args);

	CPoint topLeftPoint(std::stod(matches[2]), std::stod(matches[4]));
	double width = std::stod(matches[6]);
	double height = std::stod(matches[8]);

	uint32_t outlineColor = std::stoul(matches[10], nullptr, 16);
	uint32_t fillColor = std::stoul(matches[11], nullptr, 16);

	CRectangle rectangle(topLeftPoint, width, height, outlineColor, fillColor);

	m_shapesList.push_back(std::make_unique<CRectangle>(rectangle));
}

void CController::SetTriangle(const std::string& args)
{
	std::smatch matches = ParseString(args);

	CPoint firstVertex(std::stod(matches[2]), std::stod(matches[4]));
	CPoint secondVertex(std::stod(matches[6]), std::stod(matches[8]));
	CPoint thirdVertex(std::stod(matches[10]), std::stod(matches[12]));

	uint32_t outlineColor = std::stoul(matches[14], nullptr, 16);
	uint32_t fillColor = std::stoul(matches[14], nullptr, 16);

	CTriangle triangle(firstVertex, secondVertex, thirdVertex, outlineColor, fillColor);

	m_shapesList.push_back(std::make_unique<CTriangle>(triangle));
}

void CController::SetCircle(const std::string& args)
{
	std::smatch matches = ParseString(args);

	CPoint centralPoint(std::stod(matches[2]), std::stod(matches[4]));

	CCircle circle(centralPoint, std::stod(matches[6]), std::stoul(matches[8], nullptr, 16), std::stoul(matches[9], nullptr, 16));

	m_shapesList.push_back(std::make_unique<CCircle>(circle));
}

void CController::SetLine(const std::string& args)
{
	std::smatch matches = ParseString(args);

	CPoint firstPoint(std::stod(matches[2]), std::stod(matches[4]));
	CPoint secondPoint(std::stod(matches[6]), std::stod(matches[8]));

	CLineSegment line(firstPoint, secondPoint, std::stoul(matches[10], nullptr, 16));

	m_shapesList.push_back(std::make_unique<CLineSegment>(line));
}

void CController::WriteShapeWithMaxArea() const
{
	auto it = std::max_element(m_shapesList.begin(), m_shapesList.end(),
		[](const std::unique_ptr<IShape>& firstShape, const std::unique_ptr<IShape>& secondShape) {
			return firstShape->GetArea() < secondShape->GetArea();
		});

	m_output << (*it)->ToString() << std::endl;
}

void CController::WriteShapeWithMinPerimeter() const
{
	auto it = std::min_element(m_shapesList.begin(), m_shapesList.end(),
		[](const std::unique_ptr<IShape>& firstShape, const std::unique_ptr<IShape>& secondShape) {
			return firstShape->GetPerimeter() < secondShape->GetPerimeter();
		});

	m_output << (*it)->ToString() << std::endl;
}

void CController::Draw() const
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Result");
	CCanvas canvas(window);

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		window.clear(sf::Color(255, 255, 255));

		for (auto it = m_shapesList.begin(); it != m_shapesList.end(); it++)
		{
			(*it)->Draw(canvas);
		}

		window.display();
	}
}
