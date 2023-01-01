#pragma once

#include <map>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <optional>
#include <stdexcept>
#include <string>
#include <algorithm>
#include <set>

#include "string_functions.h"

const std::string DICTIONARY_PATH_DEFAULT = "../dictionary.txt";

struct Args
{
	std::string DictionaryPath;
};

typedef std::set<std::string> Translation;

typedef std::multimap<std::string, Translation> Dictionary;

enum class States
{
	FIND_TRANSLATION = 0,
	NEW_WORD = 1,
	NEW_TRANSLATION = 2,
	END = 3,
	END_SAVE = 4,
	END_SAVE_SUCCESS = 5,
};

void RunDictionary(std::istream& input, std::ostream& output, const std::string& dictionaryPath);

Dictionary ReadDictionary(std::istream& dictionaryFile);

void ProcessNewPosForDictionary(const std::string& word, const std::string& translations, Dictionary& dictionary);

void AddPosInDictionary(const std::string& word, const Translation& translations, Dictionary& dictionary);

void RunChat(std::istream& input, std::ostream& output, Dictionary& dictionary, bool& willSave);

std::optional<Translation> FindTranslation(const std::string& line, const Dictionary& dictionary);

void WriteDictionary(std::ostream& dictionaryFile, const Dictionary& dictionary);

void WriteMessage(std::ostream& output, const States state);

void WriteDialogSymbol(std::ostream& output, const States& state);

void WriteTranslation(std::ostream& output, const Translation& translation);

void SaveDictionary(std::ostream& output, const std::string& dictPath, const Dictionary& dictionary);


void ProcessEndStateOfChat(std::ostream& output, const std::string& line, States& state, bool& willSave);

void ProcessFindTranslationStateOfChat(std::ostream& output, const std::string& line, States& state, const Dictionary& dictionary);

void ProcessNewWordStateOfChat(std::ostream& output, const std::string& line, Dictionary& dictionary, const std::string& newWord);