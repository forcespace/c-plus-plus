#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../HTTP_URL/CHttpUrl.h"
#include "../HTTP_URL/CUrlParsingError.h"

TEST_CASE("Test functional of parsing url with exceptions")
{
	GIVEN("url = 'htt://asd.com/asd/asd'")
	{
		THEN("exception")
		{
			REQUIRE_THROWS(CHttpUrl("htt://asd.com/asd/asd"));	
			REQUIRE_THROWS_AS(CHttpUrl("htt://asd.com/asd/asd"), CUrlParsingError);	
			REQUIRE_THROWS_WITH(CHttpUrl("htt://asd.com/asd/asd"), "Wrong URL");	
		}
	}

	GIVEN("url = '//asd.com/asd/asd'")
	{
		THEN("exception")
		{
			REQUIRE_THROWS(CHttpUrl("//asd.com/asd/asd"));	
			REQUIRE_THROWS_AS(CHttpUrl("//asd.com/asd/asd"), CUrlParsingError);	
			REQUIRE_THROWS_WITH(CHttpUrl("//asd.com/asd/asd"), "Wrong URL");	
		}
	}

	GIVEN("url = 'http://asd.com:0/asd/asd'")
	{
		THEN("exception")
		{
			REQUIRE_THROWS(CHttpUrl("http://asd.com:0/asd/asd"));	
			REQUIRE_THROWS_AS(CHttpUrl("http://asd.com:0/asd/asd"), CUrlParsingError);	
			REQUIRE_THROWS_WITH(CHttpUrl("http://asd.com:0/asd/asd"), "Wrong port. Value should be in [1 .. 65535]");	
		}
	}

	GIVEN("url = 'http://asd.com:65536/asd/asd'")
	{
		THEN("exception")
		{
			REQUIRE_THROWS(CHttpUrl("http://asd.com:65536/asd/asd"));	
			REQUIRE_THROWS_AS(CHttpUrl("http://asd.com:65536/asd/asd"), CUrlParsingError);	
			REQUIRE_THROWS_WITH(CHttpUrl("http://asd.com:65536/asd/asd"), "Wrong port. Value should be in [1 .. 65535]");	
		}
	}

	GIVEN("url = 'http://asd.com:999999999/asd/asd'")
	{
		THEN("exception")
		{
			REQUIRE_THROWS(CHttpUrl("http://asd.com:999999999/asd/asd"));	
			REQUIRE_THROWS_AS(CHttpUrl("http://asd.com:999999999/asd/asd"), CUrlParsingError);	
			REQUIRE_THROWS_WITH(CHttpUrl("http://asd.com:999999999/asd/asd"), "Wrong port. Value should be in [1 .. 65535]");	
		}
	}

	GIVEN("url = 'http://asd.com:65537/asd/asd'")
	{
		THEN("exception")
		{
			REQUIRE_THROWS(CHttpUrl("http://asd.com:65537/asd/asd"));	
			REQUIRE_THROWS_AS(CHttpUrl("http://asd.com:65537/asd/asd"), CUrlParsingError);	
			REQUIRE_THROWS_WITH(CHttpUrl("http://asd.com:65537/asd/asd"), "Wrong port. Value should be in [1 .. 65535]");	
		}
	}

	GIVEN("url = 'regex.com', '/my_regex', https, 0")
	{
		THEN("exception")
		{
			REQUIRE_THROWS(CHttpUrl("regex.com", "/my_regex", Protocol::HTTPS, 0));	
			REQUIRE_THROWS_AS(CHttpUrl("regex.com", "/my_regex", Protocol::HTTPS, 0), CUrlParsingError);	
			REQUIRE_THROWS_WITH(CHttpUrl("regex.com", "/my_regex", Protocol::HTTPS, 0), "Wrong port. Value should be in [1 .. 65535]");	
		}
	}
}

TEST_CASE("Test functional of getter url and others params with rights urls")
{
	GIVEN("url = 'http://asd.com:65535/asd/asd'")
	{
		THEN("exception")
		{
			CHttpUrl url("http://asd.com:65535/asd/asd");
			REQUIRE(url.GetURL() == "http://asd.com:65535/asd/asd");
			REQUIRE(url.GetDocument() == "/asd/asd");
			REQUIRE(url.GetDomain() == "asd.com");
			REQUIRE(url.GetPort() == 65535);
			REQUIRE(url.GetProtocol() == Protocol::HTTP);
		}
	}

	GIVEN("url = 'http://asd.com:1/asd/asd'")
	{
		THEN("exception")
		{
			CHttpUrl url("http://asd.com:1/asd/asd");
			REQUIRE(url.GetURL() == "http://asd.com:1/asd/asd");
			REQUIRE(url.GetDocument() == "/asd/asd");
			REQUIRE(url.GetDomain() == "asd.com");
			REQUIRE(url.GetPort() == 1);
			REQUIRE(url.GetProtocol() == Protocol::HTTP);
		}
	}

	GIVEN("url = 'http://regex.com/my_regex'")
	{
		THEN("url = 'http://regex.com/my_regex'")
		{
			CHttpUrl url("http://regex.com/my_regex");
			REQUIRE(url.GetURL() == "http://regex.com/my_regex");
			REQUIRE(url.GetDocument() == "/my_regex");
			REQUIRE(url.GetDomain() == "regex.com");
			REQUIRE(url.GetPort() == 80);
			REQUIRE(url.GetProtocol() == Protocol::HTTP);
		}
	}

	GIVEN("url = 'HTtp://regex.com/my_regex'")
	{
		THEN("url = 'HTtp://regex.com/my_regex'")
		{
			CHttpUrl url("HTtp://regex.com/my_regex");
			REQUIRE(url.GetURL() == "http://regex.com/my_regex");
			REQUIRE(url.GetDocument() == "/my_regex");
			REQUIRE(url.GetDomain() == "regex.com");
			REQUIRE(url.GetPort() == 80);
			REQUIRE(url.GetProtocol() == Protocol::HTTP);
		}
	}

	GIVEN("url = 'https://regex.com/my_regex'")
	{
		THEN("url = 'https://regex.com/my_regex'")
		{
			CHttpUrl url("https://regex.com/my_regex");
			REQUIRE(url.GetURL() == "https://regex.com/my_regex");
			REQUIRE(url.GetDocument() == "/my_regex");
			REQUIRE(url.GetDomain() == "regex.com");
			REQUIRE(url.GetPort() == 443);
			REQUIRE(url.GetProtocol() == Protocol::HTTPS);
		}
	}

	GIVEN("url = 'https://regex.com:90/my_regex'")
	{
		THEN("url = 'https://regex.com:90/my_regex'")
		{
			CHttpUrl url("https://regex.com:90/my_regex");
			REQUIRE(url.GetURL() == "https://regex.com:90/my_regex");
			REQUIRE(url.GetDocument() == "/my_regex");
			REQUIRE(url.GetDomain() == "regex.com");
			REQUIRE(url.GetPort() == 90);
			REQUIRE(url.GetProtocol() == Protocol::HTTPS);
		}
	}

	GIVEN("url = 'https://regex.com'")
	{
		THEN("url = 'https://regex.com/'")
		{
			CHttpUrl url("https://regex.com");
			REQUIRE(url.GetURL() == "https://regex.com/");
			REQUIRE(url.GetDocument() == "/");
			REQUIRE(url.GetDomain() == "regex.com");
			REQUIRE(url.GetPort() == 443);
			REQUIRE(url.GetProtocol() == Protocol::HTTPS);
		}
	}

	GIVEN("url = 'https://regex.com/'")
	{
		THEN("url = 'https://regex.com/'")
		{
			CHttpUrl url("https://regex.com/");
			REQUIRE(url.GetURL() == "https://regex.com/");
			REQUIRE(url.GetDocument() == "/");
			REQUIRE(url.GetDomain() == "regex.com");
			REQUIRE(url.GetPort() == 443);
			REQUIRE(url.GetProtocol() == Protocol::HTTPS);
		}
	}
}

TEST_CASE("Test functional of getter url and others params with rights urls separately")
{
	GIVEN("url = 'http://regex.com/my_regex'")
	{
		THEN("url = 'regex.com', '/my_regex'")
		{
			CHttpUrl url("regex.com", "/my_regex");
			REQUIRE(url.GetURL() == "http://regex.com/my_regex");
			REQUIRE(url.GetDocument() == "/my_regex");
			REQUIRE(url.GetDomain() == "regex.com");
			REQUIRE(url.GetPort() == 80);
			REQUIRE(url.GetProtocol() == Protocol::HTTP);
		}

		THEN("url = 'regex.com', 'my_regex'")
		{
			CHttpUrl url("regex.com", "my_regex");
			REQUIRE(url.GetURL() == "http://regex.com/my_regex");
			REQUIRE(url.GetDocument() == "/my_regex");
			REQUIRE(url.GetDomain() == "regex.com");
			REQUIRE(url.GetPort() == 80);
			REQUIRE(url.GetProtocol() == Protocol::HTTP);
		}

		THEN("url = 'regex.com', 'my_regex', http")
		{
			CHttpUrl url("regex.com", "my_regex", Protocol::HTTP);
			REQUIRE(url.GetURL() == "http://regex.com/my_regex");
			REQUIRE(url.GetDocument() == "/my_regex");
			REQUIRE(url.GetDomain() == "regex.com");
			REQUIRE(url.GetPort() == 80);
			REQUIRE(url.GetProtocol() == Protocol::HTTP);
		}
	}

	GIVEN("url = 'https://regex.com/my_regex'")
	{
		THEN("url = 'regex.com', '/my_regex', https")
		{
			CHttpUrl url("regex.com", "/my_regex", Protocol::HTTPS);
			REQUIRE(url.GetURL() == "https://regex.com/my_regex");
			REQUIRE(url.GetDocument() == "/my_regex");
			REQUIRE(url.GetDomain() == "regex.com");
			REQUIRE(url.GetPort() == 443);
			REQUIRE(url.GetProtocol() == Protocol::HTTPS);
		}

		THEN("url = 'regex.com', '/my_regex', https, 423")
		{
			CHttpUrl url("regex.com", "/my_regex", Protocol::HTTPS);
			REQUIRE(url.GetURL() == "https://regex.com/my_regex");
			REQUIRE(url.GetDocument() == "/my_regex");
			REQUIRE(url.GetDomain() == "regex.com");
			REQUIRE(url.GetPort() == 443);
			REQUIRE(url.GetProtocol() == Protocol::HTTPS);
		}
	}

	GIVEN("url = 'https://regex.com:781/my_regex'")
	{
		THEN("url = 'regex.com', '/my_regex', https, 781")
		{
			CHttpUrl url("regex.com", "/my_regex", Protocol::HTTPS, 781);
			REQUIRE(url.GetURL() == "https://regex.com:781/my_regex");
			REQUIRE(url.GetDocument() == "/my_regex");
			REQUIRE(url.GetDomain() == "regex.com");
			REQUIRE(url.GetPort() == 781);
			REQUIRE(url.GetProtocol() == Protocol::HTTPS);
		}
	}
}