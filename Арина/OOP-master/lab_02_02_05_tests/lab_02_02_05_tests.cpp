#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>
#include <string>
#include "../lab_02_02_05/HtmlDecode.h"

SCENARIO("Processing of empty string gives empty string")
{
	std::string inStr = "";
	std::string outStr = "";
	std::string result = HtmlDecode(inStr);
	CHECK(result == outStr);
}

SCENARIO("Processing of string with encoded symbol gives string with decoded symbol")
{
	std::string inStr = "qwe;;&apos&apos;&gt&gt;&gt;&&gt;&amp;&apos;&lt&&lt;";
	std::string outStr = "qwe;;&apos'&gt>>&>&'&lt&<";
	std::string result = HtmlDecode(inStr);
	CHECK(result == outStr);
}