#include <fstream>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <stdlib.h>
#include <string>

constexpr int MAX_RADIX = 36;
constexpr int MIN_RADIX = 2;

int StringToInt(const std::string& value, int radix);

int CharToInt(const char ch, const int radix);
bool IsDigit(const char ch);
bool IsLetter(const char ch);
std::string ConvertNumber(const int sourceNotation, const int destinationNotation, const std::string& value);
std::string IntToString(int number, const int radix);
char IntToChar(int number, const int radix);
int UpdateNegativeNumber(int convertedNumber, int digit, int radix);
int UpdatePositiveNumber(int convertedNumber, int digit, int radix);
 
struct Args
{
	int sourceNotation;
	int destinationNotation;
	std::string value;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 4)
	{
		return std::nullopt;
	}

	int sourceNotation = StringToInt(argv[1], 10);

	if (sourceNotation > MAX_RADIX || sourceNotation < MIN_RADIX)
	{
		throw std::invalid_argument("Radix is out of range");
	}

	int destinationNotation = StringToInt(argv[2], 10);

	if (destinationNotation > MAX_RADIX || destinationNotation < MIN_RADIX)
	{
		throw std::invalid_argument("Radix is out of range");
	}

	return { { sourceNotation, destinationNotation, argv[3] } };
}

int StringToInt(const std::string& value, int radix)
{
	if (radix < MIN_RADIX || radix > MAX_RADIX)
	{
		throw std::invalid_argument("Radix is out of range");
	}

	if (value.length() == 0)
	{
		throw std::invalid_argument("There is no number");
	}

	bool isNegative = false;

	if (value[0] == '-')
	{
		isNegative = true;
	}

	int convertedNumber = 0;
	int digit = 0;

	for (int i = isNegative ? 1 : 0; i < static_cast<int>(value.length()); i++)
	{
		digit = CharToInt(value[i], radix);

		if (isNegative)
		{
			convertedNumber = UpdateNegativeNumber(convertedNumber, digit, radix);
		}
		else
		{
			convertedNumber = UpdatePositiveNumber(convertedNumber, digit, radix);
		}
	}

	return convertedNumber;
}

int UpdatePositiveNumber(int convertedNumber, int digit, int radix)
{
	if (convertedNumber > ((INT_MAX - digit) / radix))
	{
		throw std::overflow_error("Number is out of range");
	}

	return convertedNumber * radix + digit;
}

int UpdateNegativeNumber(int convertedNumber, int digit, int radix)
{
	if (convertedNumber < ((INT_MIN + digit) / radix))
	{
		throw std::overflow_error("Number is out of range");
	}

	return convertedNumber * radix - digit;
}

int CharToInt(const char ch, const int radix)
{
	if (IsDigit(ch))
	{
		if (ch - '0' >= radix)
		{
			throw std::invalid_argument("Wrong number");
		}

		return ch - '0';
	}

	if (IsLetter(ch))
	{
		if (ch - 'A' + 10 >= radix)
		{
			throw std::invalid_argument("Wrong number");
		}

		return ch - 'A' + 10;
	}

	throw std::invalid_argument("Wrong number");
}

bool IsDigit(const char ch)
{
	return ch >= '0' && ch <= '9';
}

bool IsLetter(const char ch)
{
	return ch >= 'A' && ch <= 'Z';
}

std::string ConvertNumber(const int sourceNotation, const int destinationNotation, const std::string& value)
{
	std::string convertedNumber = IntToString(StringToInt(value, sourceNotation), destinationNotation);

	return convertedNumber;
}

std::string IntToString(int number, const int radix)
{
	if (number == 0)
	{
		return "0";
	}

	if (radix < MIN_RADIX || radix > MAX_RADIX)
	{
		throw std::invalid_argument("Radix is out of range");
	}

	bool isNegative = false;
	if (number < 0)
	{
		isNegative = true;
	}

	std::string convertedNumber;

	while (number != 0)
	{
		convertedNumber = convertedNumber + IntToChar(abs(number % radix), radix);
		number = number / radix;
	}

	if (isNegative)
	{
		convertedNumber = convertedNumber + '-';
	}

	std::reverse(convertedNumber.begin(), convertedNumber.end());

	return convertedNumber;
}

char IntToChar(int number, const int radix)
{
	if (number >= radix)
	{
		throw std::invalid_argument("Wrong number");
	}

	if ((number >= 0) && (number <= 9))
	{
		return static_cast<char>('0' + number);
	}

	if ((number >= 10) && (number <= 36))
	{
		return static_cast<char>('A' + (number - 10));
	}

	throw std::invalid_argument("Wrong number");
}

int main(int argc, char* argv[])
{
	std::optional<Args> args;
	std::string convertedNumber;

	try
	{
		args = ParseArgs(argc, argv);

		if (!args.has_value())
		{
			std::cout << "Wrond input. Params should be: radix.exe <source notation> <destination notation> <value>" << std::endl;
			return 1;
		}

		convertedNumber = ConvertNumber(args->sourceNotation, args->destinationNotation, args->value);

		std::cout << convertedNumber << std::endl;
	}
	catch (const std::exception& error)
	{
		std::cout << error.what() << std::endl;
		return 1;
	}

	return 0;
}
