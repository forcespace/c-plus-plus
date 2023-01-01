#include <algorithm>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <numeric>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

typedef std::vector<std::pair<std::string, char>> HTMLDecodeList;

void DecodeText(std::istream& inFile, std::ostream& outFile);

std::string DecodeLine(const std::string_view& line, const int maxLengthOfReplacement, const HTMLDecodeList& DecodeList);

int GetMaxLengthOfReplacements(const HTMLDecodeList& chars);

char ReplaceCharNearbyPos(const std::string_view& line, size_t& substringBeginPos, const HTMLDecodeList& DecodeList);

HTMLDecodeList initHTMLDecodeList();
