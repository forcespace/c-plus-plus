/*19.13. Шахматная доска (3)
Аня разделила доску размера m × n на клетки размера
1 × 1 и раскрасила их в черный и белый цвет в шахматном
порядке. Васю заинтересовал вопрос: клеток какого цвета
получилось больше: черного или белого.
Для того чтобы выяснить это, он спросил у Ани, в
какой цвет она раскрасила j-ю клетку в i-м ряду доски. По
этой информации Вася попытался определить, клеток
какого цвета на доске больше.

Требуется написать программу, которая по размерам доски и цвету j-й клетки в i-м ряду
определит, клеток какого цвета на доске больше — черного или белого.
Petrova A, PS-22*/

#include "pch.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const string FILE_IN_NAME = "input.txt";
const string FILE_OUT_NAME = "output.txt";

bool OpenFile(ifstream& file, string fileName)
{
	file.open(fileName);
	if (file.is_open())
		return true;
	else
	{
		return false;
	}
}

void ReadInputData(int& length, int& width, int& xCoordinate, int& yCoordinate, int& color)
{
	ifstream fileForWork;
	OpenFile(fileForWork, FILE_IN_NAME);
	fileForWork >> length >> width >> xCoordinate >> yCoordinate >> color;
	fileForWork.close();
};

void PrintData(string& result)
{
	ofstream fout(FILE_OUT_NAME);
	fout << result;
	fout.close();
};

string Check(int& length, int& width, int& xCoordinate, int& yCoordinate, int& color)
{
	if ((length * width) % 2 == 0)
		return "equal";
	if (xCoordinate % 2 == 0)
	{
		if (color == 1)
			return "black";
		if (color == 0)
			return "white";
	}
	else
	{
		if (color == 1)
			return "white";
		if (color == 0)
			return "black";
	}
}

int main()
{
	int length, width, xCoordinate, yCoordinate, color = 0;
	string result = "";
	ReadInputData(length, width, xCoordinate, yCoordinate, color);
	result = Check(length, width, xCoordinate, yCoordinate, color);
	PrintData(result);
}