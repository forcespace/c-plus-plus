#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>
#include "../lab_06_01_07/CHttpUrl.h"

SCENARIO("Creating URL by string")
{
	WHEN("Full")
	{
		CHttpUrl url("https://www.ispringsolutions.com:445/ispring-suite");
		THEN("Created")
		{
			CHECK(url.GetProtocol() == Protocol::HTTPS);
			CHECK(url.GetDomain() == "www.ispringsolutions.com");
			CHECK(url.GetPort() == 445);
			CHECK(url.GetDocument() == "/ispring-suite");
		}
	}
	WHEN("Empty Port")
	{
		CHttpUrl url("https://www.ispringsolutions.com/ispring-suite");
		THEN("Created")
		{
			CHECK(url.GetProtocol() == Protocol::HTTPS);
			CHECK(url.GetDomain() == "www.ispringsolutions.com");
			CHECK(url.GetPort() == 443);
			CHECK(url.GetDocument() == "/ispring-suite");
		}
	}
	WHEN("Empty Document")
	{
		CHttpUrl url("http://www.ispringsolutions.com");
		THEN("Created")
		{
			CHECK(url.GetProtocol() == Protocol::HTTP);
			CHECK(url.GetDomain() == "www.ispringsolutions.com");
			CHECK(url.GetPort() == 80);
			CHECK(url.GetDocument() == "");
		}
	}
	WHEN("Empty Protocol")
	{
		REQUIRE_THROWS([]() {
			CHttpUrl url("www.ispringsolutions.com");
		}());
	}
	WHEN("Invalid Protocol")
	{
		REQUIRE_THROWS([]() {
			CHttpUrl url("htp://www.ispringsolutions.com");
		}());
	}
	WHEN("Invalid Port MIN")
	{
		REQUIRE_THROWS([]() {
			CHttpUrl url("https://www.ispringsolutions.com:0");
		}());
	}
	WHEN("Invalid Port MAX")
	{
		REQUIRE_THROWS([]() {
			CHttpUrl url("https://www.ispringsolutions.com:65536");
		}());
	}
}

SCENARIO("Creating URL by params without port")
{
	WHEN("Full")
	{
		CHttpUrl url("www.ispringsolutions.com", "ispring-suite", Protocol::HTTPS);
		THEN("Created")
		{
			CHECK(url.GetProtocol() == Protocol::HTTPS);
			CHECK(url.GetDomain() == "www.ispringsolutions.com");
			CHECK(url.GetPort() == 443);
			CHECK(url.GetDocument() == "/ispring-suite");
		}
	}
	WHEN("Empty Document")
	{
		REQUIRE_THROWS([]() {
			CHttpUrl url("www.ispringsolutions.com", "", Protocol::HTTP);
		}());
	}
}

SCENARIO("Creating URL by params with port")
{
	WHEN("Full")
	{
		CHttpUrl url("www.ispringsolutions.com", "ispring-suite", Protocol::HTTPS, 445);
		THEN("Created")
		{
			CHECK(url.GetProtocol() == Protocol::HTTPS);
			CHECK(url.GetDomain() == "www.ispringsolutions.com");
			CHECK(url.GetPort() == 445);
			CHECK(url.GetDocument() == "/ispring-suite");
		}
	}
	WHEN("Empty Document")
	{
		REQUIRE_THROWS([]() {
			CHttpUrl url("www.ispringsolutions.com", "", Protocol::HTTP, 445);
		}());
	}
	WHEN("Invalid Port MIN")
	{
		REQUIRE_THROWS([]() {
			CHttpUrl url("www.ispringsolutions.com", "ispring-suite", Protocol::HTTPS, 0);
		}());
	}
	WHEN("Invalid Port MAX")
	{
		REQUIRE_THROWS([]() {
			CHttpUrl url("www.ispringsolutions.com", "ispring-suite", Protocol::HTTPS, 65536);
		}());
	}
}