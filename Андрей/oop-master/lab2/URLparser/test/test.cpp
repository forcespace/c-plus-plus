#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../parser_module.h"

TEST_CASE("Test function to lower case")
{
	URL url = ParseUrl("https://fuck").value();
	REQUIRE(url.url == "https://fuck");
	REQUIRE(url.protocol == "https");
}
