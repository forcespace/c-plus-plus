#include <iostream>
#include <fstream>
#include <optional>
#include <string>
#include <functional>

const int MAX_LENGTH = 255;

enum class Mode 
{
	UNDEFINED_MODE,
	PACK_MODE,
	UNPACK_MODE
};

struct Args
{
	Mode currentMode = Mode::UNDEFINED_MODE;
	std::string inputFileName;
	std::string outputFileName;
};

#pragma pack (push)
#pragma pack(1)
struct CompressionContext
{
	char compressionChar;
	uint8_t counter = 0;
};

struct DecompressionContext
{
	char decompressionChar;
	char counter;
};
#pragma pack (pop)

Mode GetProgramMode(const std::string& modeStr)
{
	Mode currentMode = Mode::UNDEFINED_MODE;
	if (modeStr == "pack") 
	{ 
		currentMode = Mode::PACK_MODE;
	}
	else if (modeStr == "unpack") 
	{ 
		currentMode = Mode::UNPACK_MODE;
	}

	return currentMode;
}

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	bool wasError = false;
	if (argc != 4)
	{
		std::cout << "Invalid arguments count.\n"
			<< "Usage: lab_01_04_01.exe pack <input file> <output file> or lab_01_04_01.exe unpack <input file> <output file>.\n";
		return std::nullopt;
	}

	Args args;

	args.currentMode = GetProgramMode(argv[1]);
	args.inputFileName = argv[2];
	args.outputFileName = argv[3];

	return args;
}

void FlushPackResult(std::ostream& output, CompressionContext& context, char currentSymbol)
{
	if (context.counter == 0)
	{
		return;
	}

	output << (char)context.counter << context.compressionChar;
	context.compressionChar = currentSymbol;
	context.counter = (context.counter == MAX_LENGTH) ? 0 : 1;
}

bool CompressChar(CompressionContext& context, char currentSymbol, std::ostream& output)
{
	if (context.counter == 0)
	{
		context.compressionChar = currentSymbol;
	}

	if (context.compressionChar == currentSymbol)
	{
		context.counter++;
	}

	if (context.compressionChar != currentSymbol || context.counter == MAX_LENGTH)
	{
		FlushPackResult(output, context, currentSymbol);
	}

	return true;
}

bool PackFile(std::istream& input, std::ostream& output)
{
	char currentSymbol;
	CompressionContext symbolContext;
	while (input.get(currentSymbol))
	{
		CompressChar(symbolContext, currentSymbol, output);
	}
	FlushPackResult(output, symbolContext, currentSymbol);

	return true;
}

void FlushUnpackResult(std::ostream& output, const int symbolCounter, const char symbol)
{
	for (size_t i = 0; i < symbolCounter; i++)
	{
		output << symbol;
	}
}

bool DecompressChar(const DecompressionContext& context, std::ostream& output)
{
	uint8_t charCounter = static_cast<unsigned char>(context.counter);
	if (charCounter == 0)
	{
		return false;
	}
	FlushUnpackResult(output, charCounter, context.decompressionChar);
	return true;
}

bool UnpackFile(std::istream& input, std::ostream& output)
{
	DecompressionContext symbolContext;
	while (input.get(symbolContext.counter))
	{
		if (!input.get(symbolContext.decompressionChar))
		{
			std::cout << "Damaged input file\n";
			return false;
		}
		
		if (!DecompressChar(symbolContext, output))
        {
			return false;
		}
	}

	return true;
}

using Transformer = std::function<bool(std::istream& input, std::ostream& output)>;

bool TransformFile(const std::string& inputFileName, const std::string& outputFileName, const Transformer& transformer)
{
	bool result = true;
	std::ifstream input;
	std::ofstream output;

	input.open(inputFileName, std::ios::binary | std::ios::in);
	if (!input.is_open())
	{
		std::cout << "Failed to open '" << inputFileName << "' for reading\n";
		result = false;
	}

	output.open(outputFileName, std::ios::binary | std::ios::out);
	if (!output.is_open())
	{
		std::cout << "Failed to open '" << outputFileName << "' for writing\n";
		result = false;
	}

	result = transformer(input, output);

	if (input.bad())
	{
		std::cout << "Failed to read data from input file\n";
		result = false;
	}

	if (!output.flush()) // Если не удалось сбросить данные на диск
	{
		std::cout << "Failed to write data to output file\n";
		result = false;
	}

	return result;
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return 1;
	}

	bool result = true;

	switch (args->currentMode)
	{
	case Mode::PACK_MODE:
		result = TransformFile(args->inputFileName, args->outputFileName, PackFile);
		break;
	case Mode::UNPACK_MODE:
		result = TransformFile(args->inputFileName, args->outputFileName, UnpackFile);
		break;
	case Mode::UNDEFINED_MODE:
		std::cout << "Invalid mode.\n"
			<< "Usage: pack or unpack.\n";
		result = false;
		break;
	default:
		break;
	}

	return (result) ? 0 : 1;
}