/*
2.2. Путь коня (6)
Дана шахматная доска, состоящая из N x N  клеток (2 ≤ N ≤ 300), несколько из них вырезано.
Провести ходом коня через невырезанные клетки путь минимальной длины из одной заданной
клетки в другую.
Ввод из файла INPUT.TXT. В первой строке задано число N. В следующих N строках
содержится по N символов. Символом # обозначена вырезанная клетка, точкой - невырезанная
клетка, @ - заданные клетки (таких символов два).
Вывод в файл OUTPUT.TXT. Если путь построить невозможно, вывести "Impossible", в
противном случае вывести такую же карту, как и на входе, но пометить все промежуточные
положения коня символом @.

Petrova A., PS-22 2019*/

#include "pch.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

const string FILE_IN_NAME = "input.txt";
const string FILE_OUT_NAME = "output.txt";
const int MAX_QUANTITY_STR = 301;

vector<vector<string>> matrix(MAX_QUANTITY_STR, vector<string>(MAX_QUANTITY_STR));
vector<vector<string>> printMatrix(MAX_QUANTITY_STR, vector<string>(MAX_QUANTITY_STR));

const vector<pair<int, int>> HORSE_WAY = {
	{ 2, 1 },
	{ 2, -1 },
	{ -2, 1 },
	{ -2, -1 },
	{ 1, 2 },
	{ 1, -2 },
	{ -1, 2 },
	{ -1, -2 }
};

struct horseTree
{
	pair<int, int> coords;
	horseTree* parent = NULL;
};

vector<vector<horseTree*>> horseWay;

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

void ReadInputData(int& num)
{
	int quantityStr = 0;
	ifstream fileForWork;
	OpenFile(fileForWork, FILE_IN_NAME);
	fileForWork >> quantityStr;
	num = quantityStr;
	for (int i = 0; i < MAX_QUANTITY_STR; i++)
	{
		for (int j = 0; j < MAX_QUANTITY_STR; j++)
		{
			matrix[i][j] = '#';
		}
	}

	for (int i = 1; i < quantityStr + 1; i++)
	{
		for (int j = 1; j < quantityStr + 1; j++)
		{
			char temp;
			fileForWork >> temp;
			matrix[i][j] = temp;
		}
	}
	fileForWork.close();
};

/*void PrintData(int& num)
{
	ofstream fout(FILE_OUT_NAME);

	for (int i = 0; i <= num + 1; i++)
	{
		for (int j = 0; j <= num + 1; j++)
		{
			cout << matrix[i][j];
		}
		cout << endl;
	};
	fout.close();
};*/

void PrintData2(horseTree* &tree, int& num)
{
	ofstream fout(FILE_OUT_NAME);

	if (tree == NULL)
	{
		fout << "Impossible" << endl;
	}
	else
		for (int i = 1; i < num + 1; i++)
		{
			for (int j = 1; j < num + 1; j++)
			{
				fout << printMatrix[i][j];
			}
			fout << endl;
		};
	
	fout.close();
};

pair<int, int> GetStartPoint(int& num)
{
	pair<int, int> coords(0, 0);
	for (size_t i = 1; i < num + 1; i++)
	{
		for (size_t j = 1; j < num + 1; j++)
		{
			if (matrix[i][j] == "@")
			{
				matrix[i][j] = "1";
				coords.first = i;
				coords.second = j;
				return coords;
			}
		}
	}
};

/*void printVector(vector<horseTree*>& inVector)
{
	for (int i = 0; i != inVector.size(); i++)
	{
		cout << "coords ^ ";
		cout << inVector[i]->coords.first << endl;
		cout << inVector[i]->coords.second << endl;
	}
}
*/
bool IsNumber(const string& s)
{
	return all_of(s.cbegin(), s.cend(), [](const char& c) {
		return isdigit(c);
	});
}

horseTree* Move(int& num, pair<int, int> realStart, int moveNumber)
{
	horseTree* tree = NULL;
	pair<int, int> nextPosition;
	vector<horseTree*> currentIter;
	do
	{
		int lastElem = horseWay.size() - 1;
		for (size_t i = 0; i < horseWay[lastElem].size(); i++)
		{
			for (size_t j = 0; j < 8; j++)
			{
				nextPosition.first = horseWay[lastElem][i]->coords.first + HORSE_WAY[j].first;
				nextPosition.second = horseWay[lastElem][i]->coords.second + HORSE_WAY[j].second;

				if (nextPosition.first < 1)
					continue;
				if (nextPosition.first > num)
					continue;
				if (nextPosition.second < 1)
					continue;
				if (nextPosition.second > num)
					continue;
				if (matrix[nextPosition.first][nextPosition.second] == "#")
					continue;
				if (IsNumber(matrix[nextPosition.first][nextPosition.second]))
					continue;
				
				tree = new horseTree;
				tree->coords = nextPosition;
				tree->parent = horseWay[lastElem][i];
				currentIter.push_back(tree);

				if (matrix[nextPosition.first][nextPosition.second] == "@")
					return tree;

				matrix[nextPosition.first][nextPosition.second] = to_string(moveNumber);
			}
		}
		moveNumber++;
		horseWay.push_back(currentIter);
	} while (currentIter.size() > 0);

	return tree;
};

horseTree* FindHorseWayTree(int& num)
{
	horseTree* myHorseTree = NULL;
	pair<int, int> startPoint;
	startPoint = GetStartPoint(num);

	if ((startPoint.first == 0) && (startPoint.second == 0))
	{
		return NULL;
	}

	myHorseTree = new horseTree;
	myHorseTree->coords = startPoint;
	vector<horseTree*> start;
	start.push_back(myHorseTree);
	horseWay.push_back(start);
	myHorseTree = Move(num, startPoint, 2);
	return myHorseTree;
}

void PrintTree(horseTree* tree)
{
	if (tree !=NULL)
	{
		horseTree* current;
		current = tree;
		while  (current->parent != NULL)
		{
			printMatrix[current->coords.first][current->coords.second] = "@";
			current = current->parent;
		}
	}
}

int main()
{
	int quantity = 0;
	horseTree* tree = NULL;

	ReadInputData(quantity);
	printMatrix = matrix;
	tree = FindHorseWayTree(quantity);
	PrintTree(tree);
	PrintData2(tree, quantity);
}