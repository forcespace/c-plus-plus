#include "string_functions.h"

void DecodeText(std::istream& inFile, std::ostream& outFile)
{
	auto decodeList = initHTMLDecodeList();

	int maxLengthOfReplacement = GetMaxLengthOfReplacements(decodeList);

	std::string line;

	while (std::getline(inFile, line))
	{
		outFile << DecodeLine(line, maxLengthOfReplacement, decodeList) << std::endl;
	}
}

HTMLDecodeList initHTMLDecodeList()
{
	HTMLDecodeList decodeList;
	decodeList = { { "&lt;", '<' }, { "&gt;", '>' }, { "&quot;", '\"' }, { "&apos;", '\'' }, { "&amp;", '&' } };

	return decodeList;
}

std::string DecodeLine(const std::string_view& line, const int maxLengthOfReplacement, const HTMLDecodeList& decodeList)
{
	size_t cursorPos = 0;
	std::string replacedString;
	while (cursorPos < line.length())
	{
		size_t substringBeginPos = line.find('&', cursorPos);
		replacedString.append(line, cursorPos, substringBeginPos - cursorPos);

		if (substringBeginPos == std::string::npos)
		{
			break;
		}

		replacedString += ReplaceCharNearbyPos(line.substr(substringBeginPos, maxLengthOfReplacement), substringBeginPos, decodeList);

		cursorPos = substringBeginPos;
	}

	return replacedString;
}

int GetMaxLengthOfReplacements(const HTMLDecodeList& decodeList)
{
	if (decodeList.empty())
	{
		throw std::runtime_error("Replacement dictionary is empty");
	}

	size_t maxLength = 0;
	for (auto element : decodeList)
	{
		maxLength = element.first.size() > maxLength ? element.first.size() : maxLength; 
	}

	return maxLength;
}

char ReplaceCharNearbyPos(const std::string_view& line, size_t& substringBeginPos, const HTMLDecodeList& decodeList)
{
	char replacedString = '&';

	for (size_t index = 0; index < decodeList.size(); index++)
	{
		auto findReplacement = line.find(decodeList[index].first);
		if (findReplacement != std::string::npos && findReplacement == 0)
		{
			replacedString = decodeList[index].second;
			substringBeginPos += findReplacement + decodeList[index].first.size() - 1;
			break;
		}
	}

	substringBeginPos++;

	return replacedString;
}
