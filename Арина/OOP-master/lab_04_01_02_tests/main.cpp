#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <string>

#include "../lab_04_01_02/CPoint.h"
#include "../lab_04_01_02/CCircle.h"
#include "../lab_04_01_02/CLineSegment.h"
#include "../lab_04_01_02/CRectangle.h"
#include "../lab_04_01_02/CTriangle.h"
#include "../lab_04_01_02/CSession.h"

SCENARIO("Creating shapes")
{
	WHEN("Circle")
	{
		CCircle circle(CPoint(2.0, 3.0), 5.0, "ff0000", "00ff00");
		THEN("Created")
		{
			CHECK(circle.GetCenter().x() == 2.0);
			CHECK(circle.GetCenter().y() == 3.0);
			CHECK(circle.GetRadius() == 5.0);
			CHECK(circle.GetArea() == M_PI * 5.0 * 5.0);
			CHECK(circle.GetPerimeter() == 2 * M_PI * 5.0);
			CHECK(circle.GetFillColor() == 0xff0000);
			CHECK(circle.GetOutlineColor() == 0x00ff00);
		}
	}
	WHEN("Line Segment")
	{
		CLineSegment lineSegment(CPoint(2.0, 3.0), CPoint(8.0, 3.0), "ff0000");
		THEN("Created")
		{
			CHECK(lineSegment.GetStartPoint().x() == 2.0);
			CHECK(lineSegment.GetStartPoint().y() == 3.0);
			CHECK(lineSegment.GetEndPoint().x() == 8.0);
			CHECK(lineSegment.GetEndPoint().y() == 3.0);
			CHECK(lineSegment.GetArea() == 0.0);
			CHECK(lineSegment.GetPerimeter() == 6.0);
			CHECK(lineSegment.GetOutlineColor() == 0xff0000);
		}
	}
	WHEN("Rectangle")
	{
		CRectangle rectangle(CPoint(2.0, 3.0), 8.0, 3.0, "ff0000", "00ff00");
		THEN("Created")
		{
			CHECK(rectangle.GetLeftTopPoint().x() == 2.0);
			CHECK(rectangle.GetLeftTopPoint().y() == 3.0);
			CHECK(rectangle.GetWidth() == 8.0);
			CHECK(rectangle.GetHeight() == 3.0);
			CHECK(rectangle.GetArea() == 8.0 * 3.0);
			CHECK(rectangle.GetPerimeter() == 2 * (8.0 + 3.0));
			CHECK(rectangle.GetFillColor() == 0xff0000);
			CHECK(rectangle.GetOutlineColor() == 0x00ff00);
		}
	}
	WHEN("Triangle")
	{
		CTriangle triangle(CPoint(2.0, 3.0), CPoint(8.0, 3.0), CPoint(5.0, 6.0), "ff0000", "00ff00");
		THEN("Created")
		{
			CHECK(triangle.GetVertex1().x() == 2.0);
			CHECK(triangle.GetVertex1().y() == 3.0);
			CHECK(triangle.GetVertex2().x() == 8.0);
			CHECK(triangle.GetVertex2().y() == 3.0);
			CHECK(triangle.GetVertex3().x() == 5.0);
			CHECK(triangle.GetVertex3().y() == 6.0);
			CHECK(std::round(triangle.GetArea()) == 9);
			CHECK(std::round(triangle.GetPerimeter()) == 14);
			CHECK(triangle.GetFillColor() == 0xff0000);
			CHECK(triangle.GetOutlineColor() == 0x00ff00);
		}
	}
}

SCENARIO("Shapes with a maximum area and minimum perimeter")
{
	WHEN("Maximum Area")
	{
		std::stringstream strIn;
		strIn << "circle 1.0 2.0 4 ff0000 00ff00" << std::endl;
		strIn << "linesegment 2.0 3.0 4.0 5.0 ff00f0" << std::endl;
		strIn << "rectangle 3.0 4.0 2 1 ff00ff ff0fff" << std::endl;
		strIn << "triangle 0.0 0.0 5.0 6.0 3.0 4.0 f0ffff f0fff0" << std::endl;
		strIn << "exit" << std::endl;

		std::stringstream strOut;
		strOut << "  Name: Circle" << std::endl;
		strOut << "  Center point: (1, 2)" << std::endl;
		strOut << "  Radius: 4" << std::endl;
		strOut << "  Area: 50.2655" << std::endl;
		strOut << "  Perimeter: 25.1327" << std::endl;
		strOut << "  Fill color: 0xff0000" << std::endl;
		strOut << "  Outline color: 0xff00" << std::endl;

		CSession session;
		session.ProcessCommand(strIn);
		auto maxAreaShape = session.GetMaxAriaShape();
		auto maxAreaShapeInfo = session.GetShapeInfo(maxAreaShape);

		THEN("Ok")
		{
			CHECK(maxAreaShapeInfo == strOut.str());
		}
	}
	WHEN("Minimum Perimeter")
	{
		std::stringstream strIn;
		strIn << "circle 1.0 2.0 4 ff0000 00ff00" << std::endl;
		strIn << "linesegment 2.0 3.0 4.0 5.0 ff00f0" << std::endl;
		strIn << "rectangle 3.0 4.0 2 1 ff00ff ff0fff" << std::endl;
		strIn << "triangle 0.0 0.0 5.0 6.0 3.0 4.0 f0ffff f0fff0" << std::endl;
		strIn << "exit" << std::endl;

		std::stringstream strOut;
		strOut << "  Name: Line Segment" << std::endl;
		strOut << "  Start point: (2, 3)" << std::endl;
		strOut << "  End point: (4, 5)" << std::endl;
		strOut << "  Area: 0" << std::endl;
		strOut << "  Perimeter: 2.82843" << std::endl;
		strOut << "  Outline color: 0xff00f0" << std::endl;

		CSession session;
		session.ProcessCommand(strIn);
		auto minPerimeterShape = session.GetMinPerimeterShape();
		auto minPerimeterShapeInfo = session.GetShapeInfo(minPerimeterShape);

		THEN("Ok")
		{
			CHECK(minPerimeterShapeInfo == strOut.str());
		}
	}
}