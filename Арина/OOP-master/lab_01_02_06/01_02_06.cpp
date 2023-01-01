#include <iostream>
#include <fstream>
#include <optional>
#include <string>

bool IsRadixValid(const int radix)
{
	const int MIN_ALLOWED_NOTATION = 2;
	const int MAX_ALLOWED_NOTATION = 36;
	return radix >= MIN_ALLOWED_NOTATION && radix <= MAX_ALLOWED_NOTATION;
}

int CharToDigit(const char ch, const int radix, bool& wasError)
{
	wasError = false;
	int digit = -1;
	if (ch >= '0' && ch <= '9')
	{
		digit = ch - '0';
	}
	else if (ch >= 'A' && ch <= 'Z')
	{
		digit = ch - 'A' + 10;
	}
	else if (ch >= 'a' && ch <= 'z')
	{
		digit = ch - 'a' + 10;
	}
	if (digit < 0 || digit >= radix)
	{
		wasError = true;
		std::cout << "Wrong char in current notation!\n";
	}
	return (int)digit;
}

char DigitToChar(const int digit, const int radix, bool& wasError)
{
	wasError = false;
	if (!IsRadixValid(radix))
	{
		wasError = true;
		std::cout << "Notations must be between 2 and 36 value.\n";
		return '\0';
	}

	char result = '\0';
	if (digit >= 0 && digit <= 9)
	{
		result = (char)('0' + digit);
	}
	if (digit < radix && digit >= 10)
	{
		result = (char)('A' - 10 + digit);
	}
	if (result == '\0')
	{
		wasError = true;
		std::cout << "Undefined symbol in value!\n";
	}
	return result;
}

int StringToInt(const std::string& str, const int radix, bool& wasError)
{
	wasError = false;
	int result = 0;
	if (str.length() == 0)
	{
		return 0;
	}

	const int sign = (str[0] == '-') ? -1 : 1;
	const int firstDigitPosition = (str[0] == '+' || str[0] == '-') ? 1 : 0;
	
	for (size_t i = firstDigitPosition; i < str.length(); i++)
	{
		int digit = CharToDigit(str[i], radix, wasError);
		if (wasError)
		{
			return 0;
		}
		// checking limits
		if (sign > 0 && result <= (INT_MAX - digit) / radix)
		{
			result = result * radix + digit;
		}
		else if (sign < 0 && result >= (INT_MIN + digit) / radix)
		{
			result = result * radix - digit;
		}
		else
		{
			wasError = true;
			std::cout << "Value is out of limit!\n";
			return 0;
		}
	}
	return (int)sign * result;
}

std::string IntToString(const int n, const int radix, bool& wasError)
{
	wasError = false;
	if (!IsRadixValid(radix))
	{
		wasError = true;
		std::cout << "Notations must be between 2 and 36 value.\n";
		return "";
	}

	std::string resultStr = "";
	bool isNegative = n < 0; // save sign of numbers
	unsigned int number = abs(n);

	if (number == 0)
	{
		resultStr = "0";
	}

	unsigned long remainder;
	while (number > 0)
	{
		remainder = number % radix;
		number = number / radix;
		char nextCh = DigitToChar(remainder, radix, wasError);
		if (wasError)
		{
			wasError = true;
			return "";
		}
		resultStr.push_back(nextCh);
	};
	if (isNegative) resultStr.push_back('-');
	std::reverse(resultStr.begin(), resultStr.end());

	return resultStr;
}

struct Args
{
	int sourceNotation;
	int destinationNotation;
	std::string value;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	const int COMMON_NOTATION = 10;
	bool wasError = false;
	if (argc != 4)
	{
		std::cout << "Invalid arguments count.\n"
			<< "Usage: lab_01_02_06.exe <source notation> <destination notation> <value>.\n";
		return std::nullopt;
	}

	Args args;

	args.sourceNotation = StringToInt(argv[1], COMMON_NOTATION, wasError);
	if (!IsRadixValid(args.sourceNotation) || wasError)
	{
		std::cout << "Source notations must be between 2 and 36 value.\n";
		return std::nullopt;
	}

	args.destinationNotation = StringToInt(argv[2], COMMON_NOTATION, wasError);
	if (!IsRadixValid(args.destinationNotation) || wasError)
	{
		std::cout << "Destination notations must be between 2 and 36 value.\n";
		return std::nullopt;
	}

	args.value = argv[3];

	return args;
}



std::string GetConvertedNumber(const std::string& value, const int sourceNotation, 
	const int destinationNotation, bool& wasError)
{
	wasError = false;
	const int numberToConvert = StringToInt(value, sourceNotation, wasError);
	std::string convertedNumber = (!wasError) ? IntToString(numberToConvert, destinationNotation, wasError) : "";

	return convertedNumber;
}

bool ConvertNumber(const std::string& value, const int sourceNotation,
	const int destinationNotation)
{
	bool wasError = false;
	std::string convertedNumber = GetConvertedNumber(value, sourceNotation, destinationNotation, wasError);
	if (!wasError)
	{
		std::cout << convertedNumber << "\n";
	}

	return !wasError;
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return 1;
	}

	bool result = ConvertNumber(args->value, args->sourceNotation, args->destinationNotation);

	return (result) ? 0 : 1;
}
