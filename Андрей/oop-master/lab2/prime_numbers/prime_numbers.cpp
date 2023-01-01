#include "prime_module.h"

struct Args
{
	std::string stringWithNumber;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		return std::nullopt;
	}

	return { { argv[1] } };
}

int main(int argc, char* argv[])
{
    try
	{
		std::optional<Args> args = ParseArgs(argc, argv);

		if (!args.has_value())
		{
			throw std::invalid_argument("Invalid number. Try prime_number <your number>");
		}

		int upperBound = std::stoi(args->stringWithNumber);

		WriteSet(std::cout, GetPrimeNumbers(upperBound));
	}
	catch(const std::exception& error)
	{
		std::cout << error.what() << std::endl;
	}
}