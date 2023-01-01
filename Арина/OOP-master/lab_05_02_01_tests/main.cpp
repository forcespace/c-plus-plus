#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>
#include "../lab_05_02_01/CMyString.h"

TEST_CASE("Constructor (default)")
{
	CMyString myString;
	std::string emptyLine = "";
	CHECK(myString.GetLength() == 0);
	CHECK(myString.GetStringData() == emptyLine);
}

TEST_CASE("Constructor (string with the terminating character)")
{
	CMyString myString("Hello");
	std::string line = "Hello";
	CHECK(myString.GetStringData() == line);
	CHECK(myString.GetLength() == 5);
}

TEST_CASE("Constructor (character array of a given length)")
{
	char* abc = new char[5]{ 'H', 'e', 'l', 'l', 'o' };
	CMyString myString(abc, 5);
	std::string line = "Hello";
	CHECK(myString.GetStringData() == line);
	CHECK(myString.GetLength() == 5);
}

TEST_CASE("Constructor (copy)")
{
	CMyString myStringFrist("Hello");
	CMyString myStringSecond(myStringFrist);
	std::string line = "Hello";
	CHECK(myStringFrist.GetStringData() == line);
	CHECK(myStringSecond.GetStringData() == line);
	CHECK(myStringFrist.GetLength() == myStringSecond.GetLength());
}

TEST_CASE("Constructor (std::string)")
{
	WHEN("Empty")
	{
		std::string emptyLine = "";
		CMyString myString(emptyLine);
		CHECK(myString.GetStringData() == emptyLine);
		CHECK(myString.GetLength() == 0);
	}

	WHEN("Not empty")
	{
		std::string line = "Hello";
		CMyString myString(line);
		CHECK(myString.GetStringData() == line);
		CHECK(myString.GetLength() == 5);
	}
}

TEST_CASE("GetLength")
{
	WHEN("Empty")
	{
		CMyString myString;
		CHECK(myString.GetLength() == 0);
	}

	WHEN("Not empty")
	{
		CMyString myString("Hello");
		CHECK(myString.GetLength() == 5);
	}
}

TEST_CASE("GetStringData")
{
	WHEN("Empty")
	{
		CMyString myString;
		std::string emptyLine = "";
		CHECK(myString.GetStringData() == emptyLine);
	}

	WHEN("Not empty")
	{
		CMyString myString("Hello");
		std::string line = "Hello";
		CHECK(myString.GetStringData() == line);
	}
}

TEST_CASE("SubString")
{
	CMyString myString("Hello");

	WHEN("Out of range")
	{
		CHECK_THROWS(myString.SubString(10));
	}

	WHEN("Not out of range")
	{
		CMyString line(myString.SubString(3, 2));
		CHECK(line.GetStringData() == std::string("lo"));
	}

	WHEN("Not out of range (v2)")
	{
		CMyString line(myString.SubString(3, 20));
		CHECK(line.GetStringData() == std::string("lo"));
	}
}

TEST_CASE("Clear")
{
	CMyString myString("Hello");
	myString.Clear();
	CHECK(myString.GetLength() == 0);
	CHECK(myString.GetStringData() == std::string(""));
}

TEST_CASE("operator =")
{
	CMyString myString("Hello");

	WHEN("Appropriate oneself")
	{
		myString = myString;
		CHECK(myString.GetStringData() == std::string("Hello"));
		CHECK(myString.GetLength() == 5);
	}

	WHEN("Copying")
	{
		CMyString line;
		line = myString;

		CHECK(line.GetLength() == 5);
		CHECK(line.GetStringData() == std::string("Hello"));
		CHECK(myString.GetStringData() == std::string("Hello"));
	}
}

TEST_CASE("operator +")
{
	CMyString firstLine("Hello");

	WHEN("CMyString + CMyString")
	{
		CMyString secondLine(" world!");
		CMyString result = firstLine + secondLine;
		CHECK(result.GetLength() == 12);
		CHECK(result.GetStringData() == std::string("Hello world!"));
	}

	WHEN("std::string CMyString")
	{
		std::string secondLine = " world!";
		CMyString result = firstLine + secondLine;
		CHECK(result.GetLength() == 12);
		CHECK(result.GetStringData() == std::string("Hello world!"));
	}

	WHEN("const char* ñ CMyString")
	{
		const char* secondLine = new char[8]{ ' ', 'w', 'o', 'r', 'l', 'd', '!', '\0' };
		CMyString result = firstLine + secondLine;
		CHECK(result.GetLength() == 12);
		CHECK(result.GetStringData() == std::string("Hello world!"));
	}
}

TEST_CASE("operator +=")
{
	CMyString firstLine("Hello ");
	CMyString secondLine("world!");
	CMyString result("Hello world!");
	firstLine += secondLine;
	CHECK(firstLine == result);
}

TEST_CASE("operator ==")
{
	CMyString firstLine("Hello");

	WHEN("Equal lines")
	{
		CMyString secondLine("Hello");
		CHECK(firstLine == secondLine);
	}

	WHEN("Different lines")
	{
		CMyString secondLine("world");
		CHECK(!(firstLine == secondLine));
	}
}

TEST_CASE("operator !=")
{
	CMyString firstLine("Hello");

	WHEN("Equal lines")
	{
		CMyString secondLine("Hello");
		CHECK(!(firstLine != secondLine));
	}

	WHEN("Different lines")
	{
		CMyString secondLine("world");
		CHECK(firstLine != secondLine);
	}
}

TEST_CASE("operator []")
{
	CMyString myString("Hello");

	WHEN("For reading")
	{
		CHECK(myString[2] == 'l');
	}

	WHEN("For recording")
	{
		myString[2] = 'k';
		CHECK(myString[2] == 'k');
	}

	WHEN("Out of range")
	{
		CHECK_THROWS(myString[10]);
	}
}