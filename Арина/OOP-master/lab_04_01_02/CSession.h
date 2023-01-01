#pragma once
#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include <map>
#include <utility>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include "IShape.h"
#include "CPoint.h"
#include "CCircle.h"
#include "CLineSegment.h"
#include "CRectangle.h"
#include "CTriangle.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

const std::string EXIT_TEXT = "exit";

enum class Shapes
{
	Circle,
	LineSegment,
	Rectangle,
	Triangle,
};

class CSession
{
public:
	void ProcessCommand(std::istream& commands);
	std::vector<std::unique_ptr<IShape>>::const_iterator GetMaxAriaShape() const;
	std::vector<std::unique_ptr<IShape>>::const_iterator GetMinPerimeterShape() const;
	std::string GetShapeInfo(std::vector<std::unique_ptr<IShape>>::const_iterator shape) const;
	void DrawShapes() const;

private:
	void CreateShape(Shapes shape, std::vector<std::string> command);
	void CreateCircle(std::vector<std::string> command);
	void CreateLineSegment(std::vector<std::string> command);
	void CreateRectangle(std::vector<std::string> command);
	void CreateTriangle(std::vector<std::string> command);

	std::vector<std::unique_ptr<IShape>> m_shapes;
};

