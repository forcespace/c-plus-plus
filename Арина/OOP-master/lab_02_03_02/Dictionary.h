#pragma once

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <optional>
#include <vector>
#include <windows.h>
#include <boost/algorithm/string.hpp>

const std::string EXIT_TEXT = "...";
const enum UserState 
{
	WAITING_FOR_WORD,
	WAITING_FOR_TRANSLATION
};

struct Dictionary
{
	std::string fileName;
	std::multimap<std::string, std::string> dict;
	bool changed = false;
};

struct User
{
	UserState state;
	std::string newWord;
	std::string prevWord;
};

std::optional<std::string> GetDictionaryFileName(int argc, char* argv[]);
std::multimap<std::string, std::string> GetDictionaryFromFile(const std::string& fileName);
bool Translation(Dictionary& dictionary);
void ProcessInputWord(User& user, Dictionary& dictionary);
UserState ProcessWordWaiting(User& user, Dictionary& dictionary);
UserState ProcessWordTranslation(User& user, Dictionary& dictionary);
std::vector<std::string> FindTranslation(const Dictionary& dictionary, const std::string& inputWord);
void AddTranslation(User& user, Dictionary& dictionary);
void SaveDictionary(const Dictionary& dictionary, bool needSaving = false);