#include "dictionary_module.h"

void RunDictionary(std::istream& input, std::ostream& output, const std::string& dictionaryPath)
{
	std::ifstream dictionaryFile;
	dictionaryFile.open(dictionaryPath);
	Dictionary dictionary = {};
	bool willSave = false;

	if (dictionaryFile.is_open())
	{
		dictionary = ReadDictionary(dictionaryFile);
	}

	dictionaryFile.close();

	RunChat(input, output, dictionary, willSave);

	if (willSave)
	{
		SaveDictionary(output, dictionaryPath, dictionary);
	}
}

Dictionary ReadDictionary(std::istream& dictionaryFile)
{
	Dictionary dictionary;
	std::string line;
	while (getline(dictionaryFile, line))
	{
		std::stringstream iss(line);
		std::string word;
		std::string translations;

		getline(iss, word, ':');
		getline(iss, translations);

		if (!word.empty() && !translations.empty())
		{
			ProcessNewPosForDictionary(word, translations, dictionary);
		}
	}

	return dictionary;
}

void ProcessNewPosForDictionary(const std::string& word, const std::string& translations, Dictionary& dictionary)
{
	std::optional<Translation> translationsSet = GetSetFromString(GetStringInLowerCase(translations), ", ");

	if (!translationsSet.has_value())
	{
		throw std::invalid_argument("Wrong dictionary. There are no meanings of word");
	}

	AddPosInDictionary(GetStringInLowerCase(word), translationsSet.value(), dictionary);

	for (auto element : translationsSet.value())
	{
		AddPosInDictionary(element, GetSetFromString(GetStringInLowerCase(word), ", ").value(), dictionary);
	}
}

void AddPosInDictionary(const std::string& word, const Translation& translations, Dictionary& dictionary)
{
	auto it = dictionary.find(word);

	if (it == dictionary.end())
	{
		dictionary.insert(std::pair<std::string, Translation>(word, translations));
	}
	else
	{
		for (auto element : translations)
		{
			it->second.insert(element);
		}
	}
}

void RunChat(std::istream& input, std::ostream& output, Dictionary& dictionary, bool& willSave)
{
	std::string line;
	std::string newWord;
	Translation translation;
	States state = States::FIND_TRANSLATION;

	WriteDialogSymbol(output, state);
	while ((state != States::END) && getline(input, line))
	{
		if (line == "...")
		{
			state = willSave ? States::END_SAVE : States::END;
			WriteMessage(output, state);

			if (state == States::END)
			{
				break;
			}
		}

		switch (state)
		{
		case States::END:
		case States::END_SAVE:
			getline(input, line);
			ProcessEndStateOfChat(output, line, state, willSave);
			break;
		case States::FIND_TRANSLATION:
			ProcessFindTranslationStateOfChat(output, line, state, dictionary);
			if (state == States::NEW_WORD)
			{
				newWord = line;
			}
			else
			{
				WriteTranslation(output, FindTranslation(line, dictionary).value());
				WriteDialogSymbol(output, state);
			}

			break;
		case States::NEW_WORD:
			if (!line.empty())
			{
				willSave = true;
				ProcessNewWordStateOfChat(output, line, dictionary, newWord);
			}
			else
			{
				WriteDialogSymbol(output, state);
			}

			state = States::FIND_TRANSLATION;

			break;
		}
	}
}

std::optional<Translation> FindTranslation(const std::string& line, const Dictionary& dictionary)
{
	auto translation = dictionary.find(GetStringInLowerCase(line));

	if (translation == dictionary.end())
	{
		return std::nullopt;
	}

	return { translation->second };
}

void WriteMessage(std::ostream& output, const States state)
{
	switch (state)
	{
	case States::END_SAVE:
		output << "There are some changes in your dictionary. Type <yes>, if you want save it, or smth else, if you dont want it." << std::endl;
		break;
	case States::END:
		output << "Alright. See you later." << std::endl;
		break;
	case States::NEW_WORD:
		output << "There is no translation for that word. Type translation(with delimiter \", \") and dictionary will be changed, or just type empty string" << std::endl;
		break;
	case States::NEW_TRANSLATION:
		output << "New word with translation were added in dictionary" << std::endl;
		break;
	}

	WriteDialogSymbol(output, state);
}

void WriteTranslation(std::ostream& output, const Translation& translation)
{
	for (auto element : translation)
	{
		auto it = translation.end();
		it--;
		output << element << (element != *it ? ", " : "");
	}

	output << std::endl;
}

void SaveDictionary(std::ostream& output, const std::string& dictPath, const Dictionary& dictionary)
{
	output << "Dictionary will be overwritten in " << dictPath << std::endl;
	std::ofstream dictFile;

	dictFile.open(dictPath);

	if (!dictFile.is_open())
	{
		throw std::runtime_error("There are writing problems with your file.");
	}

	WriteDictionary(dictFile, dictionary);
}

void WriteDictionary(std::ostream& dictionaryFile, const Dictionary& dictionary)
{
	for (auto element : dictionary)
	{
		dictionaryFile << element.first << ':';
		WriteTranslation(dictionaryFile, element.second);
		dictionaryFile << std::endl;
	}
}

void WriteDialogSymbol(std::ostream& output, const States& state)
{
	if (state != States::END && state != States::END_SAVE_SUCCESS)
	{
		output << "> ";
	}
}

void ProcessEndStateOfChat(std::ostream& output, const std::string& line, States& state, bool& willSave)
{
	willSave = false;
	if (GetStringInLowerCase(line) == "yes")
	{
		willSave = true;
		WriteMessage(output, States::END_SAVE_SUCCESS);
	}

	state = States::END;

	WriteMessage(output, state);
}

void ProcessFindTranslationStateOfChat(std::ostream& output, const std::string& line, States& state, const Dictionary& dictionary)
{
	auto it = FindTranslation(line, dictionary);

	if (!it.has_value() && line != "...")
	{
		state = States::NEW_WORD;
		WriteMessage(output, state);
	}
}

void ProcessNewWordStateOfChat(std::ostream& output, const std::string& line, Dictionary& dictionary, const std::string& newWord)
{
	ProcessNewPosForDictionary(newWord, line, dictionary);
	WriteMessage(output, States::NEW_TRANSLATION);
}
