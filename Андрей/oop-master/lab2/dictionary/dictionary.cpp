#include "dictionary_module.h"

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		return std::nullopt;
	}

	return { { argv[1] } };
}

int main(int argv, char* argc[])
{
	std::optional<Args> args = ParseArgs(argv, argc);

	std::string dictionaryPath = DICTIONARY_PATH_DEFAULT;

	if (args.has_value())
	{
		dictionaryPath = args->DictionaryPath;
	}
	
	try
	{
		RunDictionary(std::cin, std::cout, dictionaryPath);
	}
	catch (const std::exception& error)
	{
		std::cout << error.what() << std::endl;
	}
	return 0;
}