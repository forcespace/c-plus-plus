#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../CCircle.h"
#include "../CController.h"
#include "../CLineSegment.h"
#include "../CPoint.h"
#include "../CRectangle.h"
#include "../CTriangle.h"
#include "CMockCanvas.h"
#include "../common_libs.h"

TEST_CASE("Test class CPoint")
{
	WHEN("Point x = 0; y = 0")
	{
		CPoint point(0, 0);

		THEN("x = 0; y = 0")
		{
			REQUIRE(point.x == 0);
			REQUIRE(point.y == 0);
		}
	}

	WHEN("Point x = -10; y = 10")
	{
		CPoint point(-10, 10);

		THEN("x = -10; y = 10")
		{
			REQUIRE(point.x == -10);
			REQUIRE(point.y == 10);
		}
	}

	WHEN("Point x = 124.123; y = -110.123")
	{
		CPoint point(124.123, -110.123);

		THEN("x = 124.123; y = -110.123")
		{
			REQUIRE(point.x == 124.123);
			REQUIRE(point.y == -110.123);
		}
	}

	WHEN("Points (1, 2) (2, 1)")
	{
		CPoint firstPoint(1, 2);
		CPoint secondPoint(2, 1);

		THEN("Points are not equal")
		{
			REQUIRE(!CPoint::Equal(firstPoint, secondPoint));
		}
	}

	WHEN("Points (0, 1) (0, -1)")
	{
		CPoint firstPoint(0, 1);
		CPoint secondPoint(0, -1);

		THEN("Points are not equal")
		{
			REQUIRE(!CPoint::Equal(firstPoint, secondPoint));
		}
	}

	WHEN("Points (0, 0) (0, 0)")
	{
		CPoint firstPoint(0, 0);
		CPoint secondPoint(0, 0);

		THEN("Points are equal")
		{
			REQUIRE(CPoint::Equal(firstPoint, secondPoint));
		}
	}
}

TEST_CASE("Test class CLineSegment")
{
	WHEN("Line (1, 1)(2, 2)")
	{
		CPoint firstPoint(1, 1);
		CPoint secondPoint(2, 2);
		CLineSegment line(firstPoint, secondPoint, 0xfff000);

		THEN("area = 0; perimeter = sqrt(2); color = yellow")
		{
			REQUIRE(line.GetArea() == 0);
			REQUIRE(line.GetPerimeter() == sqrt(2));
			REQUIRE(line.GetOutlineColor() == 0xfff000);
			REQUIRE(CPoint::Equal(line.GetStartPoint(), firstPoint));
			REQUIRE(CPoint::Equal(line.GetEndPoint(), secondPoint));
		}
	}

	WHEN("Line (1, 1)(1, -10)")
	{
		CPoint firstPoint(1, 1);
		CPoint secondPoint(1, -10);
		CLineSegment line(firstPoint, secondPoint, 0xffffff);

		THEN("area = 0; perimeter = 11; color = white")
		{
			REQUIRE(line.GetArea() == 0);
			REQUIRE(line.GetPerimeter() == 11);
			REQUIRE(line.GetOutlineColor() == 0xffffff);
			REQUIRE(CPoint::Equal(line.GetStartPoint(), firstPoint));
			REQUIRE(CPoint::Equal(line.GetEndPoint(), secondPoint));
		}
	}

	WHEN("Line (1, 1)(1, 1)")
	{
		CPoint firstPoint(1, 1);
		CPoint secondPoint(1, 1);
		CLineSegment line(firstPoint, secondPoint, 0xffffff);

		THEN("area = 0; perimeter = 0; color = white")
		{
			REQUIRE(line.GetArea() == 0);
			REQUIRE(line.GetPerimeter() == 0);
			REQUIRE(line.GetOutlineColor() == 0xffffff);
			REQUIRE(CPoint::Equal(line.GetStartPoint(), firstPoint));
			REQUIRE(CPoint::Equal(line.GetEndPoint(), secondPoint));
		}

		THEN("description will be right")
		{
			std::string description = "line with points "
									  "(1.0, 1.0), (1.0, 1.0), "
									  "outline color: #ffffff";

			REQUIRE(line.ToString() == description);
		}
	}
}

TEST_CASE("Test class CTriangle")
{
	WHEN("Triangle (1, 1)(1, 4)(5, 4) 'right triangle'")
	{
		CPoint firstPoint(1, 1);
		CPoint secondPoint(1, 4);
		CPoint thirdPoint(5, 4);

		CTriangle triangle(firstPoint, secondPoint, thirdPoint, 0xffffff, 0xffffff);

		THEN("area = 6; perimeter = 12; fill color = white, outline color = white")
		{
			REQUIRE(triangle.GetArea() == 6);
			REQUIRE(triangle.GetPerimeter() == 12);
			REQUIRE(triangle.GetOutlineColor() == 0xffffff);
			REQUIRE(triangle.GetFillColor() == 0xffffff);
			REQUIRE(CPoint::Equal(triangle.GetVertex1(), firstPoint));
			REQUIRE(CPoint::Equal(triangle.GetVertex2(), secondPoint));
			REQUIRE(CPoint::Equal(triangle.GetVertex3(), thirdPoint));
		}

		THEN("description will be right")
		{
			std::string description = "triangle with points "
									  "(1.0, 1.0), (1.0, 4.0), (5.0, 4.0), "
									  "outline color: #ffffff and fill color: #ffffff";

			REQUIRE(triangle.ToString() == description);
		}
	}

	WHEN("Triangle (1, 1)(1, 4)(3, 3) 'acute-angled triangle'")
	{
		CPoint firstPoint(1, 1);
		CPoint secondPoint(1, 4);
		CPoint thirdPoint(3, 3);

		CTriangle triangle(firstPoint, secondPoint, thirdPoint, 0xffffff, 0xffffff);

		THEN("area = 3; perimeter = sqrt(8) + sqrt(5) + 3; fill color = white, outline color = white")
		{
			REQUIRE(triangle.GetArea() > 0);
			REQUIRE(triangle.GetPerimeter() == sqrt(8) + sqrt(5) + 3);
			REQUIRE(triangle.GetOutlineColor() == 0xffffff);
			REQUIRE(triangle.GetFillColor() == 0xffffff);
			REQUIRE(CPoint::Equal(triangle.GetVertex1(), firstPoint));
			REQUIRE(CPoint::Equal(triangle.GetVertex2(), secondPoint));
			REQUIRE(CPoint::Equal(triangle.GetVertex3(), thirdPoint));
		}
	}

	WHEN("Triangle (-1, 2)(2, 0)(4, 2) 'obtuse triangle'")
	{
		CPoint firstPoint(-1, 2);
		CPoint secondPoint(2, 0);
		CPoint thirdPoint(4, 2);

		CTriangle triangle(firstPoint, secondPoint, thirdPoint, 0xffffff, 0xffffff);

		THEN("area = 5; perimeter = sqrt(8) + sqrt(13) + 5; fill color = white, outline color = white")
		{
			REQUIRE(triangle.GetArea() > 0);
			REQUIRE(triangle.GetPerimeter() == sqrt(8) + sqrt(13) + 5);
			REQUIRE(triangle.GetOutlineColor() == 0xffffff);
			REQUIRE(triangle.GetFillColor() == 0xffffff);
			REQUIRE(CPoint::Equal(triangle.GetVertex1(), firstPoint));
			REQUIRE(CPoint::Equal(triangle.GetVertex2(), secondPoint));
			REQUIRE(CPoint::Equal(triangle.GetVertex3(), thirdPoint));
		}
	}

	WHEN("Triangle (-1, 2)(-1, 2)(-1, 2) 'wrong triangle, dot'")
	{
		CPoint firstPoint(-1, 2);
		CPoint secondPoint(-1, 2);
		CPoint thirdPoint(-1, 2);

		CTriangle triangle(firstPoint, secondPoint, thirdPoint, 0xffffff, 0xffffff);

		THEN("area = 0; perimeter = 0; fill color = white, outline color = white")
		{
			REQUIRE(triangle.GetArea() == 0);
			REQUIRE(triangle.GetPerimeter() == 0);
			REQUIRE(triangle.GetOutlineColor() == 0xffffff);
			REQUIRE(triangle.GetFillColor() == 0xffffff);
			REQUIRE(CPoint::Equal(triangle.GetVertex1(), firstPoint));
			REQUIRE(CPoint::Equal(triangle.GetVertex2(), secondPoint));
			REQUIRE(CPoint::Equal(triangle.GetVertex3(), thirdPoint));
		}
	}
}

TEST_CASE("Test class CRectangle")
{
	WHEN("Rectangle (5, 5)  width = 5 height = 5")
	{
		CPoint topLeftPoint(5, 5);
		CPoint bottomRightPoint(10, 0);

		CRectangle rectangle(topLeftPoint, 5, 5, 0xffffff, 0xffffff);

		THEN("area = 25; perimeter = 20; fill color = white, outline color = white")
		{
			REQUIRE(rectangle.GetArea() == 25);
			REQUIRE(rectangle.GetPerimeter() == 20);
			REQUIRE(rectangle.GetOutlineColor() == 0xffffff);
			REQUIRE(rectangle.GetFillColor() == 0xffffff);
			REQUIRE(rectangle.GetWidth() == 5);
			REQUIRE(rectangle.GetHeight() == 5);
			REQUIRE(CPoint::Equal(rectangle.GetTopLeftPoint(), topLeftPoint));
			REQUIRE(CPoint::Equal(rectangle.GetBottomRightPoint(), bottomRightPoint));
		}
	}

	WHEN("Rectangle (10, 10)  width = 5.5 height = 10")
	{
		CPoint topLeftPoint(10, 10);
		CPoint bottomRightPoint(15.5, 0);

		CRectangle rectangle(topLeftPoint, 5.5, 10, 0xffffff, 0xffffff);

		THEN("area = 55; perimeter = 31; fill color = white, outline color = white")
		{
			REQUIRE(rectangle.GetArea() == 55);
			REQUIRE(rectangle.GetPerimeter() == 31);
			REQUIRE(rectangle.GetWidth() == 5.5);
			REQUIRE(rectangle.GetHeight() == 10);
			REQUIRE(rectangle.GetOutlineColor() == 0xffffff);
			REQUIRE(rectangle.GetFillColor() == 0xffffff);
			REQUIRE(CPoint::Equal(rectangle.GetTopLeftPoint(), topLeftPoint));
			REQUIRE(CPoint::Equal(rectangle.GetBottomRightPoint(), bottomRightPoint));
		}

		THEN("description will be right")
		{
			std::string description = "rectangle with top left point "
									  "(10.0, 10.0), width: 5.5 and height: 10.0, "
									  "outline color: #ffffff and fill color: #ffffff";

			REQUIRE(rectangle.ToString() == description);
		}
	}

	WHEN("Rectangle (10, 10)  width = 0 height = 0")
	{
		CPoint topLeftPoint(10, 10);
		CPoint bottomRightPoint(10, 10);

		CRectangle rectangle(topLeftPoint, 0, 0, 0xffffff, 0xffffff);

		THEN("area = 0; perimeter = 0; fill color = white, outline color = white")
		{
			REQUIRE(rectangle.GetArea() == 0);
			REQUIRE(rectangle.GetPerimeter() == 0);
			REQUIRE(rectangle.GetWidth() == 0);
			REQUIRE(rectangle.GetHeight() == 0);
			REQUIRE(rectangle.GetOutlineColor() == 0xffffff);
			REQUIRE(rectangle.GetFillColor() == 0xffffff);
			REQUIRE(CPoint::Equal(rectangle.GetTopLeftPoint(), topLeftPoint));
			REQUIRE(CPoint::Equal(rectangle.GetBottomRightPoint(), bottomRightPoint));
		}
	}
}

TEST_CASE("Test class CCircle")
{
	WHEN("Circle (5, 5) raduis = 4")
	{
		CPoint centralPoint(5, 5);

		CCircle circle(centralPoint, 4, 0xffffff, 0xffffff);

		THEN("area = 50.24; perimeter = 25.12; fill color = white, outline color = white")
		{
			REQUIRE(circle.GetArea() == 50.24);
			REQUIRE(circle.GetPerimeter() == 25.12);
			REQUIRE(circle.GetOutlineColor() == 0xffffff);
			REQUIRE(circle.GetFillColor() == 0xffffff);
			REQUIRE(circle.GetRadius() == 4);
			REQUIRE(CPoint::Equal(circle.GetCentralPoint(), centralPoint));
		}

		THEN("description will be right")
		{
			std::string description = "circle with center "
									  "(5.0, 5.0), radius: 4.0, "
									  "outline color: #ffffff and fill color: #ffffff";

			REQUIRE(circle.ToString() == description);
		}
	}

	WHEN("Circle (5, 5) raduis = 0")
	{
		CPoint centralPoint(5, 5);

		CCircle circle(centralPoint, 0, 0xffffff, 0xffffff);
		
		THEN("area = 0; perimeter = 0; fill color = white, outline color = white")
		{
			REQUIRE(circle.GetArea() == 0);
			REQUIRE(circle.GetPerimeter() == 0);
			REQUIRE(circle.GetRadius() == 0);
			REQUIRE(circle.GetOutlineColor() == 0xffffff);
			REQUIRE(circle.GetFillColor() == 0xffffff);
			REQUIRE(CPoint::Equal(circle.GetCentralPoint(), centralPoint));
		}
	}
}

TEST_CASE("test functional of drawing")
{
	GIVEN("circle")
	{
		CPoint firstPoint(5, 5);
		CPoint secondPoint(10, 10);

		CLineSegment line(firstPoint, secondPoint, 0xffffff);

		WHEN("call draw")
		{
			CMockCanvas mockCanvas;

			line.Draw(mockCanvas);

			THEN("draw line will be in notifications")
			{
				std::vector<CMockCanvas::Notification> notifications = {
					CMockCanvas::Notification::DrawLine
				};

				REQUIRE(mockCanvas.GetNotifications() == notifications);
			}

			THEN("draw circle will be not in notifications")
			{
				std::vector<CMockCanvas::Notification> notifications = {
					CMockCanvas::Notification::DrawCircle
				};

				REQUIRE(mockCanvas.GetNotifications() != notifications);
			}

			THEN("draw polygon will be not in notifications")
			{
				std::vector<CMockCanvas::Notification> notifications = {
					CMockCanvas::Notification::DrawPolygon
				};

				REQUIRE(mockCanvas.GetNotifications() != notifications);
			}
		}
	}

	GIVEN("circle")
	{
		CPoint centralPoint(5, 5);

		CCircle circle(centralPoint, 4, 0xffffff, 0xffffff);

		WHEN("call draw")
		{
			CMockCanvas mockCanvas;

			circle.Draw(mockCanvas);

			THEN("draw circle will be in notifications")
			{
				std::vector<CMockCanvas::Notification> notifications = {
					CMockCanvas::Notification::DrawCircle
				};

				REQUIRE(mockCanvas.GetNotifications() == notifications);
			}
		}
	}

	GIVEN("rectangle")
	{
		CPoint rightTopPoint(5, 5);

		CRectangle rectangle(rightTopPoint, 4, 4, 0xffffff, 0xffffff);

		WHEN("call draw")
		{
			CMockCanvas mockCanvas;

			rectangle.Draw(mockCanvas);

			THEN("draw circle will be in notifications")
			{
				std::vector<CMockCanvas::Notification> notifications = {
					CMockCanvas::Notification::DrawPolygon
				};

				REQUIRE(mockCanvas.GetNotifications() == notifications);
			}
		}
	}

	GIVEN("triangle")
	{
		CPoint firstVertex(5, 5);
		CPoint secondVertex(6, 6);
		CPoint thirdVertex(3, 12);

		CTriangle triangle(firstVertex, secondVertex, thirdVertex, 0xffffff, 0xffffff);

		WHEN("call draw")
		{
			CMockCanvas mockCanvas;

			triangle.Draw(mockCanvas);

			THEN("draw circle will be in notifications")
			{
				std::vector<CMockCanvas::Notification> notifications = {
					CMockCanvas::Notification::DrawPolygon
				};

				REQUIRE(mockCanvas.GetNotifications() == notifications);
			}
		}
	}

	GIVEN("triangle, circle and line")
	{
		CPoint firstVertex(5, 5);
		CPoint secondVertex(6, 6);
		CPoint thirdVertex(3, 12);
		CTriangle triangle(firstVertex, secondVertex, thirdVertex, 0xffffff, 0xffffff);

		CPoint centralPoint(5, 5);
		CCircle circle(centralPoint, 4, 0xffffff, 0xffffff);

		CPoint firstPoint(5, 5);
		CPoint secondPoint(10, 10);
		CLineSegment line(firstPoint, secondPoint, 0xffffff);

		WHEN("call draw (triangle, circle, line)")
		{
			CMockCanvas mockCanvas;

			triangle.Draw(mockCanvas);
			circle.Draw(mockCanvas);
			line.Draw(mockCanvas);

			THEN("draw triangle, circle, line will be in notifications")
			{
				std::vector<CMockCanvas::Notification> notifications = {
					CMockCanvas::Notification::DrawPolygon,
					CMockCanvas::Notification::DrawCircle,
					CMockCanvas::Notification::DrawLine,
				};

				REQUIRE(mockCanvas.GetNotifications() == notifications);
			}
		}
	}
}