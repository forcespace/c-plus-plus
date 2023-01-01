#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../dictionary_module.h"

TEST_CASE("Test without repeats and many meanings")
{
	Dictionary dictionary = {};
	ProcessNewPosForDictionary("cat", "�����", dictionary);
	ProcessNewPosForDictionary("dog", "������", dictionary);
	ProcessNewPosForDictionary("parrot", "�������", dictionary);
	ProcessNewPosForDictionary("rabbit", "�������� ������", dictionary);
	REQUIRE(FindTranslation("rabbit", dictionary).value() == std::set<std::string>{ "�������� ������" });
	REQUIRE(!FindTranslation("owl", dictionary).has_value());
}

TEST_CASE("Test without repeats but with two or more meanings on word")
{
	Dictionary dictionary = {};
	ProcessNewPosForDictionary("cat", "�����, �������������", dictionary);
	ProcessNewPosForDictionary("dog", "������", dictionary);
	ProcessNewPosForDictionary("dog", "������ ���� �������", dictionary);
	ProcessNewPosForDictionary("dog", "������������ ��������� ���� �������", dictionary);
	REQUIRE(FindTranslation("cat", dictionary).value().size() == 2);
	REQUIRE(FindTranslation("cat", dictionary).value() == std::set<std::string>{ "�����", "�������������" });

	REQUIRE(FindTranslation("dog", dictionary).value().size() == 3);
	REQUIRE(FindTranslation("dog", dictionary).value() == std::set<std::string>{ "������", "������ ���� �������", "������������ ��������� ���� �������" });
}

TEST_CASE("Test with bidirectional translation")
{
	Dictionary dictionary = {};
	ProcessNewPosForDictionary("cat", "�����, �������������, ���� ��������", dictionary);
	ProcessNewPosForDictionary("dog", "������, ���� ��������", dictionary);
	ProcessNewPosForDictionary("dog", "������ ���� �������", dictionary);
	ProcessNewPosForDictionary("dog", "������������ ��������� ���� �������", dictionary);
	REQUIRE(FindTranslation("���� ��������", dictionary).value().size() == 2);
	REQUIRE(FindTranslation("���� ��������", dictionary).value() == std::set<std::string>{ "cat", "dog" });
	REQUIRE(FindTranslation("������ ���� �������", dictionary).value() == std::set<std::string>{ "dog" });
}

TEST_CASE("Test function to lower case")
{
	REQUIRE(GetStringInLowerCase("12 pm, night, silence") == "12 pm, night, silence");
	REQUIRE(GetStringInLowerCase("SnOW AND lonELIness OuTSiDe tHe windoW") == "snow and loneliness outside the window");
	REQUIRE(GetStringInLowerCase("WHY AND WHAT FOR?") == "why and what for?");
	REQUIRE(GetStringInLowerCase("��� ����� ������?") == "��� ����� ������?");
}

TEST_CASE("Test with case-independent")
{
	Dictionary dictionary = {};
	ProcessNewPosForDictionary("cat", "�����, �������������", dictionary);
	ProcessNewPosForDictionary("CAT", "���� ��������", dictionary);
	ProcessNewPosForDictionary("DOG", "������", dictionary);
	ProcessNewPosForDictionary("Dog", "������ ���� �������", dictionary);
	ProcessNewPosForDictionary("dOG", "������������ ��������� ���� �������", dictionary);
	REQUIRE(FindTranslation("cat", dictionary).value().size() == 3);
	REQUIRE(FindTranslation("CAt", dictionary).value().size() == 3);
	REQUIRE(FindTranslation("caT", dictionary).value() == std::set<std::string>{ "�����", "�������������", "���� ��������" });

	REQUIRE(FindTranslation("DOG", dictionary).value().size() == 3);
	REQUIRE(FindTranslation("DOG", dictionary).value() == std::set<std::string>{ "������", "������ ���� �������", "������������ ��������� ���� �������" });
}