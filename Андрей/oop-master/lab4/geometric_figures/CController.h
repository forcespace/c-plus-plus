#pragma once
#include "common_libs.h"
#include "IShape.h"

class CController
{
public:
	CController(std::istream& input, std::ostream& output);

	void GetShape() const;

	void WriteAllInfoAboutShapes() const;

	void Draw() const;

	void SetRectangle(const std::string& args);

	void SetLine(const std::string& args);

	void SetTriangle(const std::string& args);

	void SetCircle(const std::string& args);

	void GetHelp(const std::string& args) const;

private:

	void WriteShapeWithMaxArea() const;

	void WriteShapeWithMinPerimeter() const;

	std::smatch ParseString(const std::string& args) const;

	using ShapesList = std::vector<std::unique_ptr<IShape>>;

	using Handler = std::function<void(const std::string& args)>;

	using ActionMap = std::map<std::string, Handler>;

	std::istream& m_input;

	std::ostream& m_output;

	ShapesList m_shapesList;

	const ActionMap m_actionMap;
};
