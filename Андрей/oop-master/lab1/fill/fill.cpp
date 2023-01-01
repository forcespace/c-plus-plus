#include <fstream>
#include <iomanip>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>

#define MATRIX_ROW 100
#define MATRIX_COLUMN 100

typedef char Matrix[MATRIX_ROW][MATRIX_COLUMN];

void GetContours(std::string& inputPath, Matrix& matrix);
void ReadMatrix(std::ifstream& inputFile, Matrix& matrix);
void OutputContours(std::string& outputPath, Matrix& matrix);
void OutputMatrix(std::ofstream& outputFile, Matrix& matrix);
void PrepareMatrix(Matrix& matrix);
void FillContour(Matrix& contours);
void FillPlaceNearbyDot(Matrix& matrix, const int matrixRow, const int matrixColumn);

struct Args
{
	std::string inputPath;
	std::string outputPath;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 3)
	{
		return std::nullopt;
	}

	return { { argv[1], argv[2] } };
}

bool IsPermissibleSymbol(char symbol)
{
	return symbol == ' ' || symbol == 'O' || symbol == '#';
}

void GetContours(std::string& inputPath, Matrix& matrix)
{
	std::ifstream inputFile;
	inputFile.open(inputPath);

	if (!inputFile.is_open())
	{
		throw std::invalid_argument("Input file does not open");
	}

	ReadMatrix(inputFile, matrix);
}

void ReadMatrix(std::ifstream& inputFile, Matrix& matrix)
{
	char symbol;
	int matrixRow = 0;
	int matrixColumn = 0;
	bool wasStart = false;
	while (inputFile >> std::noskipws >> symbol)
	{
		if (matrixColumn <= 99 && matrixRow <= 99)
		{
			switch (symbol)
			{
			case 'O':
				wasStart = true;
			case '#':
			case ' ':
				matrix[matrixRow][matrixColumn] = symbol;
				matrixColumn++;
				break;
			case '\n':
				matrixRow++;
				matrixColumn = 0;
				break;
			default:
				throw std::invalid_argument("Wrong contour");
				break;
			}

			if (inputFile.bad())
			{
				throw std::runtime_error("Problem with reading file");
			}
		}
		else
		{
			matrixRow = matrixRow % 100;
			matrixColumn = matrixColumn % 100;
		}
	}

	if (!wasStart)
	{
		throw std::invalid_argument("There are no start");
	}
}

void PrepareMatrix(Matrix& matrix)
{
	for (int matrixRow = 0; matrixRow < MATRIX_ROW; matrixRow++)
	{
		for (int matrixColumn = 0; matrixColumn < MATRIX_COLUMN; matrixColumn++)
		{
			matrix[matrixRow][matrixColumn] = ' ';
		}
	}
}

void OutputContours(std::string& outputPath, Matrix& matrix)
{
	std::ofstream outputFile;
	outputFile.open(outputPath);

	if (!outputFile.is_open())
	{
		throw std::invalid_argument("Output file does not open");
	}

	OutputMatrix(outputFile, matrix);

	if (!outputFile.flush())
	{
		throw std::invalid_argument("Output file is flush");
	}
}

void OutputMatrix(std::ofstream& outputFile, Matrix& matrix)
{
	for (int matrixRow = 0; matrixRow < MATRIX_ROW; matrixRow++)
	{
		for (int matrixColumn = 0; matrixColumn < MATRIX_COLUMN; matrixColumn++)
		{
			outputFile << matrix[matrixRow][matrixColumn];
		}

		outputFile << std::endl;
	}
}

void FillContour(Matrix& matrix)
{
	for (int matrixRow = 0; matrixRow < MATRIX_ROW; matrixRow++)
	{
		for (int matrixColumn = 0; matrixColumn < MATRIX_COLUMN; matrixColumn++)
		{
			if (matrix[matrixRow][matrixColumn] == 'O')
			{
				FillPlaceNearbyDot(matrix, matrixRow, matrixColumn);
			}
		}
	}
}

void FillPlaceNearbyDot(Matrix& matrix, const int matrixRow, const int matrixColumn)
{
	if (matrix[matrixRow][matrixColumn] == ' ')
	{
		matrix[matrixRow][matrixColumn] = '.';
	}

	if (matrixRow > 0 && matrix[matrixRow - 1][matrixColumn] == ' ')
	{
		FillPlaceNearbyDot(matrix, matrixRow - 1, matrixColumn);
	}

	if (matrixColumn < 99 && matrix[matrixRow][matrixColumn + 1] == ' ')
	{
		FillPlaceNearbyDot(matrix, matrixRow, matrixColumn + 1);
	}

	if (matrixColumn > 0 && matrix[matrixRow][matrixColumn - 1] == ' ')
	{
		FillPlaceNearbyDot(matrix, matrixRow, matrixColumn - 1);
	}

	if (matrixRow < 99 && matrix[matrixRow + 1][matrixColumn] == ' ')
	{
		FillPlaceNearbyDot(matrix, matrixRow + 1, matrixColumn);
	}
}

int main(int argc, char* argv[])
{
	std::optional<Args> args;

	args = ParseArgs(argc, argv);
	if (!args.has_value())
	{
		std::cout << "Wrond input. Params should be: fill.exe <matrix input file> <matrix output file>" << std::endl;
		return 1;
	}

	try
	{
		Matrix contours;
		PrepareMatrix(contours);
		GetContours(args->inputPath, contours);
		FillContour(contours);
		OutputContours(args->outputPath, contours);
	}
	catch (const std::exception& error)
	{
		std::cout << error.what() << std::endl;
		return 1;
	}

	return 0;
}
