#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../string_functions.h"

TEST_CASE("Unnecessarily decode text")
{
	std::istringstream iss("Hello, i am text without any html symbols");
	std::ostringstream oss;
	DecodeText(iss, oss);
	REQUIRE(oss.str() == "Hello, i am text without any html symbols\n");
}

TEST_CASE("Unnecessarily decode text with &")
{
	std::istringstream iss("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&;;;;;;;;;;;&;&;&;&;&&&&;;");
	std::ostringstream oss;
	DecodeText(iss, oss);
	REQUIRE(oss.str() == "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&;;;;;;;;;;;&;&;&;&;&&&&;;\n");
}

TEST_CASE("Text with simply html symbols")
{
	std::istringstream iss("Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s");
	std::ostringstream oss;
	DecodeText(iss, oss);
	REQUIRE(oss.str() == "Cat <says> \"Meow\". M&M's\n");
}

TEST_CASE("Text with first and last chars of html symbols")
{
	std::istringstream iss("Hello &&&&quo;;;&;&;&&;;&;");
	std::ostringstream oss;

	DecodeText(iss, oss);
	REQUIRE(oss.str() == "Hello &&&&quo;;;&;&;&&;;&;\n");
}

TEST_CASE("Text with first fake and last chars of html symbols")
{
	std::istringstream iss("&quotHello &&&&quo;;;&;&;&&;;&&lt;");
	std::ostringstream oss;

	DecodeText(iss, oss);
	REQUIRE(oss.str() == "&quotHello &&&&quo;;;&;&;&&;;&<\n");
}

TEST_CASE("Text with not max lenght of substitute substring")
{
	std::istringstream iss("&;&lt;");
	std::ostringstream oss;

	DecodeText(iss, oss);
	REQUIRE(oss.str() == "&;<\n");
}

TEST_CASE("Empty string")
{
	std::istringstream iss("");
	std::ostringstream oss;

	DecodeText(iss, oss);
	REQUIRE(oss.str() == "");
}
