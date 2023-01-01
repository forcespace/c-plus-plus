#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>

#include "../lab_02_03_02/Dictionary.h"
#include <windows.h>

bool AreFilesTheSame(const std::string& fileName1, const std::string& fileName2)
{
	bool result = true;
	std::ifstream file1;
	std::ifstream file2;

	file1.open(fileName1);
	file2.open(fileName2);
	if (!file1.is_open() || !file2.is_open())
	{
		return false;
	}

	while (!file1.eof() && !file2.eof()) 
	{
		if (file1.get() != file2.get()) return false;
	}

	result = (file1.eof() && file2.eof()) ? true : false;
	file1.close();
	file2.close();
	return result;
}

SCENARIO("Copy existing dictionary and save.")
{
	int argc = 2;
	char args[][255] = { "lab_02_03_02.exe", "tests/add_translation_to_existing_dictionary_test.txt" };
	char* argv[2];
	argv[0] = &args[0][0];
	argv[1] = &args[1][0];

	Dictionary dictionary;
	dictionary.fileName = *GetDictionaryFileName(argc, argv);
	dictionary.dict = GetDictionaryFromFile("tests/add_translation_to_existing_dictionary.txt");
	SaveDictionary(dictionary, true);
	CHECK(AreFilesTheSame("tests/add_translation_to_existing_dictionary.txt", "tests/add_translation_to_existing_dictionary_test.txt") == true);
}

SCENARIO("Add translation to new (empty) dictionary and save.")
{
	int argc = 2;
	char args[][255] = { "lab_02_03_02.exe", "tests/add_translation_to_new_dictionary_test.txt" };
	char* argv[2];
	argv[0] = &args[0][0];
	argv[1] = &args[1][0];

	Dictionary dictionary;
	dictionary.fileName = *GetDictionaryFileName(argc, argv);
	dictionary.dict = GetDictionaryFromFile("tests/add_translation_to_new_dictionary.txt");
	User user;
	user.prevWord = "user";
	user.newWord = "пользователь";
	AddTranslation(user, dictionary);
	SaveDictionary(dictionary, true);
	CHECK(AreFilesTheSame("tests/add_translation_to_new_dictionary.txt", "tests/add_translation_to_new_dictionary_test.txt") == true);
}

SCENARIO("Find one existing translation.")
{
	Dictionary dictionary;
	dictionary.dict = { {"hi", "привет"} , {"hello", "привет"} , {"regards", "привет"} };
	std::vector<std::string> translation = FindTranslation(dictionary, std::string("hi"));
	CHECK(translation.size() == 1);
	CHECK(translation[0] == std::string("привет"));
}

SCENARIO("Find multiple existing translation.")
{
	Dictionary dictionary;
	dictionary.dict = { {"hello", "привет"} , {"hi", "привет"} , {"regards", "привет"} };
	std::vector<std::string> translation = FindTranslation(dictionary, std::string("привет"));
	CHECK(translation.size() == 3);
	CHECK(translation[0] == std::string("hello"));
	CHECK(translation[1] == std::string("hi"));
	CHECK(translation[2] == std::string("regards"));
}