#include "string_functions.h"

std::optional<std::set<std::string>> GetSetFromString(const std::string_view& line, const std::string& separator)
{
	std::set<std::string> words;
	std::string word;

	size_t cursorPos = 0;

	while (cursorPos < line.size())
	{
		size_t substringBeginPos = line.find(separator, cursorPos);

		if (substringBeginPos == std::string::npos)
		{
			word = line.substr(cursorPos, line.size() - cursorPos);
			words.insert(word);

			break;
		}

		word = line.substr(cursorPos, substringBeginPos - cursorPos);
		words.insert(word);

		cursorPos = substringBeginPos + separator.size();
	}

	return { words };
}

std::string GetStringInLowerCase(const std::string& line)
{
	std::string stringInLowerCase;
	for (auto element: line)
	{
		stringInLowerCase += tolower(element);
	}

	return stringInLowerCase;
}