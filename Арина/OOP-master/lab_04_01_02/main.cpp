#include "CSession.h"

int main()
{
	CSession session;
	std::cout << "This program finds a shape with a maximum area and minimum perimeter." << std::endl;
	std::cout << "To exit, enter \"exit\"." << std::endl;
	session.ProcessCommand(std::cin);

	std::cout << std::endl << "Max Area Shape:" << std::endl;
	std::cout << session.GetShapeInfo(session.GetMaxAriaShape()) << std::endl;
	std::cout << std::endl << "Min Perimeter Shape:" << std::endl;
	std::cout << session.GetShapeInfo(session.GetMinPerimeterShape()) << std::endl;
	session.DrawShapes();

	return 0;
}