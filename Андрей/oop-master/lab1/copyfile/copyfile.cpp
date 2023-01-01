#include <fstream>
#include <iostream>

struct Args
{
	std::string inputPath;
	std::string outputPath;
};

int copyFile(std::ifstream& inputFile, std::ofstream& outputFile)
{
	char ch;
	while (inputFile.get(ch))
	{
		if (!outputFile.put(ch))
		{
			std::cout << "Failed to save copy";
			return 1;
		}
	}

	if (!outputFile.flush())
	{
		std::cout << "Failed to copy data";
		return 1;
	}

	return 0;
}

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cout << "Wrond input. Params should be: copyfile.exe <input file name> <output file name>" << std::endl;
		return 1;
	}

	struct Args args = { argv[1], argv[2] };

	std::ifstream inputFile;
	inputFile.open(args.inputPath);
	if (!inputFile.is_open())
	{
		std::cout << "Input file does not opened" << std::endl;
		return 1;
	}

	std::ofstream outputFile;
	outputFile.open(args.outputPath);
	if (!outputFile.is_open())
	{
		std::cout << "Output file does not opened" << std::endl;
		return 1;
	}

	if (copyFile(inputFile, outputFile) == 1)
	{
		return 1;
	}

	return 0;
}
