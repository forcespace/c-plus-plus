#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../MyString/CMyString.h"
#include "../MyString/common_libs.h"

TEST_CASE("Test functional of constructors")
{
	GIVEN("string 'hello\0'")
	{
		CMyString string("hello");

		THEN("lenght is 5 and string is 'hello'")
		{
			REQUIRE(string.GetLength() == 5);
			REQUIRE(string == "hello");
			REQUIRE(string[5] == '\0');
		}
	}

	GIVEN("string ''")
	{
		CMyString string;

		THEN("lenght is 0 and string is '\0'")
		{
			REQUIRE(string.GetLength() == 0);
			REQUIRE(string[0] == '\0');
		}
	}

	GIVEN("string '', that created by empty string")
	{
		CMyString string("");

		THEN("lenght is 0 and string is '\0'")
		{
			REQUIRE(string.GetLength() == 0);
			REQUIRE(string[0] == '\0');
		}
	}

	GIVEN("string 'hello' with length 0")
	{
		CMyString string("hello", 0);

		THEN("lenght is 0 and string is '\0'")
		{
			REQUIRE(string.GetLength() == 0);
			REQUIRE(string[0] == '\0');
		}
	}

	GIVEN("string 'hello world' with fixed length 5")
	{
		CMyString string("hello world", 5);

		THEN("lenght is 5 and string is 'hello\0'")
		{
			REQUIRE(string.GetLength() == 5);
			REQUIRE(string == "hello");
			REQUIRE(string[5] == '\0');
		}
	}

	GIVEN("string 'hello world' with fixed length -5")
	{
		THEN("exception: 'Error, length is < 0'")
		{
			REQUIRE_THROWS(CMyString("hello world", -5));
		}
	}

	GIVEN("string 'hello world', that created by copying")
	{
		CMyString string("hello world");
		CMyString copiedString = string;

		THEN("lenght is 11 and string is 'hello world\0'")
		{
			REQUIRE(copiedString.GetLength() == 11);
			REQUIRE(copiedString == "hello world");

			REQUIRE(copiedString[11] == '\0');
		}
	}

	GIVEN("string '', that created by copying")
	{
		CMyString copiedString = CMyString("");

		THEN("lenght is 0 and string is '\0'")
		{
			REQUIRE(copiedString.GetLength() == 0);
			REQUIRE(copiedString[0] == '\0');
		}
	}

	GIVEN("string '', that stl string")
	{
		std::string emptyStlString = "";
		CMyString copiedString(emptyStlString);

		THEN("lenght is 0 and string is '\0'")
		{
			REQUIRE(copiedString.GetLength() == 0);
			REQUIRE(copiedString[0] == '\0');
		}
	}

	GIVEN("string 'hello', that is stl string")
	{
		std::string helloStlString = "hello";
		CMyString copiedString = helloStlString;

		THEN("lenght is 5 and string is 'hello\0'")
		{
			REQUIRE(copiedString.GetLength() == 5);
			REQUIRE(copiedString == "hello");
		}
	}
}

TEST_CASE("Test functional of substring")
{
	GIVEN("string 'hello'")
	{
		CMyString string = "hello";

		WHEN("substring(5, 4)")
		{
			THEN("string: ''")
			{
				CMyString substring = string.GetSubString(5, 4);

				REQUIRE(substring.GetLength() == 0);
				REQUIRE(substring[0] == '\0');
			}
		}

		WHEN("substring(500, 4)")
		{
			THEN("exception: 'Wrong params'")
			{
				REQUIRE_THROWS(string.GetSubString(500, 4));
			}
		}

		WHEN("substring(4, 4)")
		{
			THEN("string: 'o'")
			{
				CMyString substring = string.GetSubString(4, 4);

				REQUIRE(substring.GetLength() == 1);
				REQUIRE(substring == "o");
				REQUIRE(substring[1] == '\0');
			}
		}

		WHEN("substring(0)")
		{
			THEN("string: 'hello'")
			{
				CMyString substring = string.GetSubString(0);

				REQUIRE(substring.GetLength() == 5);
				REQUIRE(substring == "hello");
				REQUIRE(substring[5] == '\0');
			}
		}

		WHEN("substring(0, 1230)")
		{
			THEN("string: 'hello'")
			{
				CMyString substring = string.GetSubString(0, 1230);

				REQUIRE(substring.GetLength() == 5);
				REQUIRE(substring == "hello");
				REQUIRE(substring[5] == '\0');
			}
		}

		WHEN("substring(0, 4)")
		{
			THEN("string: 'hell'")
			{
				CMyString substring = string.GetSubString(0, 4);

				REQUIRE(substring.GetLength() == 4);
				REQUIRE(substring == "hell");
				REQUIRE(substring[4] == '\0');
			}
		}

		WHEN("substring(0, 3)")
		{
			THEN("string: 'hel'")
			{
				CMyString substring = string.GetSubString(0, 3);

				REQUIRE(substring.GetLength() == 3);
				REQUIRE(substring == "hel");
				REQUIRE(substring[3] == '\0');
			}
		}

		WHEN("substring(0, 2)")
		{
			THEN("string: 'he'")
			{
				CMyString substring = string.GetSubString(0, 2);

				REQUIRE(substring.GetLength() == 2);
				REQUIRE(substring == "he");
				REQUIRE(substring[2] == '\0');
			}
		}

		WHEN("substring(1, 2)")
		{
			THEN("string: 'el'")
			{
				CMyString substring = string.GetSubString(1, 2);

				REQUIRE(substring.GetLength() == 2);
				REQUIRE(substring == "el");
				REQUIRE(substring[2] == '\0');
			}
		}

		WHEN("substring(2, 1)")
		{
			THEN("string: 'l'")
			{
				CMyString substring = string.GetSubString(2, 1);

				REQUIRE(substring.GetLength() == 1);
				REQUIRE(substring == "l");
				REQUIRE(substring[1] == '\0');
			}
		}
	}
}

TEST_CASE("Test functional of assign")
{
	GIVEN("s = 'hello' b = 'bonjour'")
	{
		CMyString s = "hello";
		CMyString b = "bonjour";

		WHEN("s = b")
		{
			s = b;

			THEN("s = 'bonjour'")
			{
				REQUIRE(s.GetLength() == 7);
				REQUIRE(s == "bonjour");
				REQUIRE(s[7] == '\0');
			}

			THEN("b = 'bonjour'")
			{
				REQUIRE(b == "bonjour");
				REQUIRE(b[7] == '\0');
			}
		}

		WHEN("b = s")
		{
			b = s;

			THEN("b = 'hello'")
			{
				REQUIRE(s.GetLength() == 5);
				REQUIRE(s == "hello");
				REQUIRE(s[5] == '\0');
			}

			THEN("s = 'hello'")
			{
				REQUIRE(b == "hello");
				REQUIRE(b[5] == '\0');
			}
		}

		WHEN("s = s")
		{
			s = s;

			THEN("s = 'hello'")
			{
				REQUIRE(s.GetLength() == 5);
				REQUIRE(s == "hello");
				REQUIRE(s[5] == '\0');
			}
		}

		WHEN("s = ''")
		{
			s = "";

			THEN("s = ''")
			{
				REQUIRE(s.GetLength() == 0);
				REQUIRE(s[0] == '\0');
			}
		}
	}
}

TEST_CASE("Test functional of + and +=")
{
	GIVEN("s = 'qw' b = 'ert'")
	{
		CMyString s = "qw";
		CMyString b = "ert";

		WHEN("s = s + b")
		{
			s = s + b;

			THEN("s = 'qwert'")
			{
				REQUIRE(s.GetLength() == 5);
				REQUIRE(s == "qwert");
				REQUIRE(s[5] == '\0');
			}
		}

		WHEN("s += b")
		{
			s += b;

			THEN("s = 'qwert'")
			{
				REQUIRE(s.GetLength() == 5);
				REQUIRE(s == "qwert");
				REQUIRE(s[5] == '\0');
			}
		}

		WHEN("s = '' + b")
		{
			s = "" + b;

			THEN("s = 'ert'")
			{
				REQUIRE(s.GetLength() == 3);
				REQUIRE(s == "ert");
				REQUIRE(s[3] == '\0');
			}
		}

		WHEN("s = b + ''")
		{
			s = b + "";

			THEN("s = 'ert'")
			{
				REQUIRE(s.GetLength() == 3);
				REQUIRE(s == "ert");
				REQUIRE(s[3] == '\0');
			}
		}
	}

	GIVEN("s = 'test'")
	{
		CMyString s = "test";

		WHEN("s = '1' + s")
		{
			s = "1" + s;

			THEN("s = '1test'")
			{
				REQUIRE(s.GetLength() == 5);
				REQUIRE(s == "1test");
				REQUIRE(s[5] == '\0');
			}
		}

		WHEN("s += '1'")
		{
			s += "1";

			THEN("s = 'test1'")
			{
				REQUIRE(s.GetLength() == 5);
				REQUIRE(s == "test1");
				REQUIRE(s[5] == '\0');
			}
		}

		WHEN("s = '1' + '23'")
		{
			std::string number = "1";
			s = number + "23";

			THEN("s = '123'")
			{
				REQUIRE(s.GetLength() == 3);
				REQUIRE(s == "123");
				REQUIRE(s[3] == '\0');
			}
		}

		WHEN("s += '1' string")
		{
			std::string number = "1";
			s += number;

			THEN("s = 'test1'")
			{
				REQUIRE(s.GetLength() == 5);
				REQUIRE(s == "test1");
				REQUIRE(s[5] == '\0');
			}
		}
	}
}

TEST_CASE("Test functional of ==")
{
	GIVEN("s = 'qw' b = 'ert'")
	{
		CMyString s = "qw";
		CMyString b = "ert";

		THEN("s != b")
		{
			REQUIRE_FALSE(s == b);
			REQUIRE(s != b);
		}
	}

	GIVEN("s = 'qw' b = 'ert' string")
	{
		std::string s = "qw";
		std::string b = "ert";

		THEN("s != b")
		{
			REQUIRE_FALSE(s == b);
			REQUIRE(s != b);
		}
	}

	GIVEN("s = 'qw' b = 'ert' char*")
	{
		const char* s = "qw";
		const char* b = "ert";

		THEN("s != b")
		{
			REQUIRE_FALSE(s == b);
			REQUIRE(s != b);
		}
	}

	GIVEN("s = 'qw' b = 'ww'")
	{
		CMyString s = "qw";
		CMyString b = "ww";

		THEN("s != b")
		{
			REQUIRE_FALSE(s == b);
			REQUIRE(s != b);
		}
	}

	GIVEN("s = 'qw' b = 'ww' string")
	{
		std::string s = "qw";
		std::string b = "ww";

		THEN("s != b")
		{
			REQUIRE_FALSE(s == b);
			REQUIRE(s != b);
		}
	}

	GIVEN("s = 'qw' b = 'ww' char*")
	{
		const char* s = "qw";
		const char* b = "ww";

		THEN("s != b")
		{
			REQUIRE_FALSE(s == b);
			REQUIRE(s != b);
		}
	}

	GIVEN("s = 'qw' b = 'qw'")
	{
		CMyString s = "qw";
		CMyString b = "qw";

		THEN("s == b")
		{
			REQUIRE_FALSE(s != b);
			REQUIRE(s == b);
		}
	}

	GIVEN("s = 'qw' b = 'qw' string")
	{
		std::string s = "qw";
		std::string b = "qw";

		THEN("s == b")
		{
			REQUIRE_FALSE(s != b);
			REQUIRE(s == b);
		}
	}

	GIVEN("s = 'qw' b = 'qw' char*")
	{
		const char* s = "qw";
		const char* b = "qw";

		THEN("s == b")
		{
			REQUIRE_FALSE(s != b);
			REQUIRE(s == b);
		}
	}

	GIVEN("s = 'qw' and 'qwe'")
	{
		CMyString s = "qw";

		THEN("s != 'qwe'")
		{
			REQUIRE_FALSE(s == "qwe");
			REQUIRE(s != "qwe");
		}
	}

	GIVEN("s = 'qwe' and 'qwe'")
	{
		CMyString s = "qwe";

		THEN("s == 'qwe'")
		{
			REQUIRE_FALSE(s != "qwe");
			REQUIRE(s == "qwe");
		}
	}
}

TEST_CASE("Test functional of << and >>")
{
	GIVEN("'test' in iss")
	{
		CMyString string;
		std::istringstream iss("test\0");
		std::ostringstream oss;

		WHEN("iss >> string")
		{
			iss >> string;

			THEN("string == 'test'")
			{
				REQUIRE(string == "test");
				REQUIRE(string[4] == '\0');
			}
		}
	}

	GIVEN("'test' in string")
	{
		CMyString string = "test";
		std::ostringstream oss;

		WHEN("oss << string")
		{
			THEN("in oss - 'test'")
			{
				oss << string;
				REQUIRE(oss.str() == "test");
			}
		}
	}
}

TEST_CASE("Test functional of [] for reading and writing")
{
	GIVEN("string = 'test'")
	{
		CMyString string = "test";

		WHEN("string[0] for reading")
		{
			THEN("string[0] = 't'")
			{
				REQUIRE(string[0] == 't');
				REQUIRE(string[0] != 'e');
			}
		}

		WHEN("string[1] for reading")
		{
			THEN("string[1] = 'e'")
			{
				REQUIRE(string[1] == 'e');
				REQUIRE(string[1] != 't');
			}
		}

		WHEN("string[2] for reading")
		{
			THEN("string[2] = 's'")
			{
				REQUIRE(string[2] == 's');
				REQUIRE(string[2] != 't');
			}
		}

		WHEN("string[3] for reading")
		{
			THEN("string[3] = 't'")
			{
				REQUIRE(string[3] == 't');
				REQUIRE(string[3] != 's');
			}
		}

		WHEN("string[0] = 'a'")
		{
			string[0] = 'a';
			THEN("string = 'aest'")
			{
				REQUIRE(string[0] == 'a');
				REQUIRE(string == "aest");
			}
		}

		WHEN("string[5]")
		{
			THEN("exception")
			{
				REQUIRE_THROWS(string[5]);
			}
		}
	}

	GIVEN("string = ''")
	{
		CMyString string;

		WHEN("string[0]")
		{
			THEN("exception")
			{
				REQUIRE(string[0] == '\0');
			}
		}
	}
}

TEST_CASE("Test functional of >, >=, <, <=")
{
	GIVEN("string1 = 'abc', string2 = 'abcd'")
	{
		CMyString string1 = "abc";
		CMyString string2 = "abcd";

		THEN("string1 < string2")
		{
			REQUIRE(string1 < string2);
			REQUIRE(string1 <= string2);
			REQUIRE_FALSE(string1 > string2);
			REQUIRE_FALSE(string1 >= string2);
		}
	}

	GIVEN("string1 = 'bc', string2 = 'abcd'")
	{
		CMyString string1 = "bc";
		CMyString string2 = "abcd";

		THEN("string1 > string2")
		{
			REQUIRE(string1 > string2);
			REQUIRE(string1 >= string2);
			REQUIRE_FALSE(string1 < string2);
			REQUIRE_FALSE(string1 <= string2);
		}

		THEN("string2 < string1")
		{
			REQUIRE(string2 < string1);
			REQUIRE(string2 <= string1);
			REQUIRE_FALSE(string2 > string1);
			REQUIRE_FALSE(string2 >= string1);
		}
	}

	GIVEN("string1 = 'bc', string2 = 'bc'")
	{
		CMyString string1 = "bc";
		CMyString string2 = "bc";

		THEN("string1 == string2")
		{
			REQUIRE_FALSE(string1 > string2);
			REQUIRE(string1 >= string2);
			REQUIRE_FALSE(string1 < string2);
			REQUIRE(string1 <= string2);
		}
	}

	GIVEN("string1 = 'abc', string2 = 'acc'")
	{
		CMyString string1 = "abc";
		CMyString string2 = "acc";

		THEN("string1 < string2")
		{
			REQUIRE_FALSE(string1 > string2);
			REQUIRE_FALSE(string1 >= string2);
			REQUIRE(string1 < string2);
			REQUIRE(string1 <= string2);
		}

		THEN("string2 > string1")
		{
			REQUIRE(string2 > string1);
			REQUIRE(string2 >= string1);
			REQUIRE_FALSE(string2 < string1);
			REQUIRE_FALSE(string2 <= string1);
		}
	}
}
