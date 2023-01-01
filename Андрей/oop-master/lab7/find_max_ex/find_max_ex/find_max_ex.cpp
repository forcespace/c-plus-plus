#include <iomanip>
#include <iostream>

#include "find_max.h"
#include "sportsman_module.h"

int main()
{
	std::vector<Sportsman> sportsmen = {
		{ "Karanbek Abdul", 170.1, 90.5 },
		{ "Daxadaev Mahach", 164.3, 54.4 },
		{ "Aleev Muhu", 201.5, 106.0 },
		{ "Daklunbek Ulug", 183.6, 86.7 },
		{ "Zuravelbek Abuldaren", 183.6, 120.9 }
	};

	Sportsman tallestSportsman;
	Sportsman heaviestSportsman;

	if (FindMaxEx(sportsmen, tallestSportsman, [](const Sportsman& first, const Sportsman& second) { return first.height < second.height; }))
	{
		std::cout << "The tallest sportsman is " << tallestSportsman.name << std::endl;
	}
	else
	{
		std::cout << "Some error with searching the tallest sportsman";	
	}
	
	if (FindMaxEx(sportsmen, heaviestSportsman, [](Sportsman first, Sportsman second) { return first.weight < second.weight; }))
	{
		std::cout << "The heaviest sportsman is " << heaviestSportsman.name << std::endl;
	}
	else
	{
		std::cout << "Some error with searching the heaviest sportsman";
	}

	return 0;
}
