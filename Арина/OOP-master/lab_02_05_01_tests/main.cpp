#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>

#include "../lab_02_05_01/UrlParser.h"

SCENARIO("Get protocol.")
{
	CHECK(GetProtocol("http") == Protocol::HTTP);
	CHECK(GetProtocol("https") == Protocol::HTTPS);
	CHECK(GetProtocol("ftp") == Protocol::FTP);
}

SCENARIO("Get port.")
{
	CHECK(GetPort("", Protocol::HTTP)  == 80);
	CHECK(GetPort("", Protocol::HTTPS) == 443);
	CHECK(GetPort("", Protocol::FTP)   == 21);
	CHECK(GetPort("80", Protocol::HTTP) == 80);
	CHECK(GetPort("85", Protocol::HTTP) == 85);
}

SCENARIO("Parse URL.")
{
	std::string url = "http://www.mysite.com/docs/document1.html?page=30&lang=en#title";
	Protocol protocol;
	int port;
	std::string host;
	std::string document;
	auto primes = ParseURL(url, protocol, port, host, document);
	CHECK(protocol == Protocol::HTTP);
	CHECK(port == 80);
	CHECK(host == "www.mysite.com");
	CHECK(document == "/docs/document1.html?page=30&lang=en#title");

	url = "www.mysite.com";
	primes = ParseURL(url, protocol, port, host, document);
	CHECK(protocol == Protocol::HTTP);
	CHECK(port == 80);
	CHECK(host == "www.mysite.com");
	CHECK(document == "");

	url = "www.mysite.com:56/docs/document1.html?page=30&lang=en#title";
	primes = ParseURL(url, protocol, port, host, document);
	CHECK(protocol == Protocol::HTTP);
	CHECK(port == 56);
	CHECK(host == "www.mysite.com");
	CHECK(document == "/docs/document1.html?page=30&lang=en#title");
}