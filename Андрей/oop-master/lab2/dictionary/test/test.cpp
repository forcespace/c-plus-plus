#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../dictionary_module.h"

TEST_CASE("Test without repeats and many meanings")
{
	Dictionary dictionary = {};
	ProcessNewPosForDictionary("cat", "кошка", dictionary);
	ProcessNewPosForDictionary("dog", "собака", dictionary);
	ProcessNewPosForDictionary("parrot", "попугай", dictionary);
	ProcessNewPosForDictionary("rabbit", "пугливый кролик", dictionary);
	REQUIRE(FindTranslation("rabbit", dictionary).value() == std::set<std::string>{ "пугливый кролик" });
	REQUIRE(!FindTranslation("owl", dictionary).has_value());
}

TEST_CASE("Test without repeats but with two or more meanings on word")
{
	Dictionary dictionary = {};
	ProcessNewPosForDictionary("cat", "кошка, необщительная", dictionary);
	ProcessNewPosForDictionary("dog", "собака", dictionary);
	ProcessNewPosForDictionary("dog", "лучший друг человек", dictionary);
	ProcessNewPosForDictionary("dog", "единственный настоящий друг человек", dictionary);
	REQUIRE(FindTranslation("cat", dictionary).value().size() == 2);
	REQUIRE(FindTranslation("cat", dictionary).value() == std::set<std::string>{ "кошка", "необщительная" });

	REQUIRE(FindTranslation("dog", dictionary).value().size() == 3);
	REQUIRE(FindTranslation("dog", dictionary).value() == std::set<std::string>{ "собака", "лучший друг человек", "единственный настоящий друг человек" });
}

TEST_CASE("Test with bidirectional translation")
{
	Dictionary dictionary = {};
	ProcessNewPosForDictionary("cat", "кошка, необщительная, друг человека", dictionary);
	ProcessNewPosForDictionary("dog", "собака, друг человека", dictionary);
	ProcessNewPosForDictionary("dog", "лучший друг человек", dictionary);
	ProcessNewPosForDictionary("dog", "единственный настоящий друг человек", dictionary);
	REQUIRE(FindTranslation("друг человека", dictionary).value().size() == 2);
	REQUIRE(FindTranslation("друг человека", dictionary).value() == std::set<std::string>{ "cat", "dog" });
	REQUIRE(FindTranslation("лучший друг человек", dictionary).value() == std::set<std::string>{ "dog" });
}

TEST_CASE("Test function to lower case")
{
	REQUIRE(GetStringInLowerCase("12 pm, night, silence") == "12 pm, night, silence");
	REQUIRE(GetStringInLowerCase("SnOW AND lonELIness OuTSiDe tHe windoW") == "snow and loneliness outside the window");
	REQUIRE(GetStringInLowerCase("WHY AND WHAT FOR?") == "why and what for?");
	REQUIRE(GetStringInLowerCase("Что такое любовь?") == "Что такое любовь?");
}

TEST_CASE("Test with case-independent")
{
	Dictionary dictionary = {};
	ProcessNewPosForDictionary("cat", "кошка, необщительная", dictionary);
	ProcessNewPosForDictionary("CAT", "друг человека", dictionary);
	ProcessNewPosForDictionary("DOG", "собака", dictionary);
	ProcessNewPosForDictionary("Dog", "лучший друг человек", dictionary);
	ProcessNewPosForDictionary("dOG", "единственный настоящий друг человек", dictionary);
	REQUIRE(FindTranslation("cat", dictionary).value().size() == 3);
	REQUIRE(FindTranslation("CAt", dictionary).value().size() == 3);
	REQUIRE(FindTranslation("caT", dictionary).value() == std::set<std::string>{ "кошка", "необщительная", "друг человека" });

	REQUIRE(FindTranslation("DOG", dictionary).value().size() == 3);
	REQUIRE(FindTranslation("DOG", dictionary).value() == std::set<std::string>{ "собака", "лучший друг человек", "единственный настоящий друг человек" });
}