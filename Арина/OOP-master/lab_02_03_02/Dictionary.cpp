#include "Dictionary.h"

std::optional<std::string> GetDictionaryFileName(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "The dictionary has not been set.\n";
		std::cout << "The default is dictionary_common.txt.\n";
		return "dictionary_common.txt";
	}

	return argv[1];
}

std::multimap<std::string, std::string> GetDictionaryFromFile(const std::string& fileName)
{
	std::multimap<std::string, std::string> dictionary;
	std::string fileStr;
	std::ifstream dictionaryFile(fileName);
	while (getline(dictionaryFile, fileStr))
	{
		std::vector<std::string> dictionaryPair;
		boost::split(dictionaryPair, fileStr, [](char c) {return c == ' ';});
		dictionary.insert(std::pair<std::string, std::string>(dictionaryPair[0], dictionaryPair[1]));
	}
	dictionaryFile.close();

	return dictionary;
}

bool Translation(Dictionary& dictionary)
{
	std::string inputWord;
	User user;
	user.state = WAITING_FOR_WORD;

	while (true)
	{
		getline(std::cin, user.newWord);
		if (user.newWord == EXIT_TEXT) break;
		ProcessInputWord(user, dictionary);
	}

	return dictionary.changed;
}

void ProcessInputWord(User& user, Dictionary& dictionary)
{
	switch (user.state)
	{
		case WAITING_FOR_WORD:
			user.state = ProcessWordWaiting(user, dictionary);
			break;
		case WAITING_FOR_TRANSLATION:
			user.state = ProcessWordTranslation(user, dictionary);
			break;
		default:
			break;
	}
	user.prevWord = user.newWord;
}

UserState ProcessWordWaiting(User& user, Dictionary& dictionary)
{
	if (user.newWord.length() == 0)
	{
		return WAITING_FOR_WORD;
	}
	std::vector<std::string> translations = FindTranslation(dictionary, user.newWord);
	if (translations.size() == 0) 
	{
		std::cout << "There is no \"" << user.newWord << "\" in dictionary yet." << std::endl;
		std::cout << "Write the translation or press enter to skip." << std::endl;
		return WAITING_FOR_TRANSLATION;
	}
	else 
	{
		std::cout << "The following translations were found for the word:" << std::endl;
		std::copy(translations.begin(), translations.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
		std::cout << "Write the next word or press \"...\" to exit." << std::endl;
		return WAITING_FOR_WORD;
	}
}

UserState ProcessWordTranslation(User& user, Dictionary& dictionary)
{
	AddTranslation(user, dictionary);
	return WAITING_FOR_WORD;
}

std::vector<std::string> FindTranslation(const Dictionary& dictionary, const std::string& inputWord)
{
	std::vector<std::string> translations;
	std::string lowerInputWord = boost::to_lower_copy(inputWord);
	for (auto it = dictionary.dict.begin(); it != dictionary.dict.end(); ++it)
	{
		const std::string translationFirst = boost::to_lower_copy((*it).first);
		const std::string translationSecond = boost::to_lower_copy((*it).second);
		if (lowerInputWord == translationFirst)  translations.push_back((*it).second);
		if (lowerInputWord == translationSecond) translations.push_back((*it).first);
	}
	return translations;
}

void AddTranslation(User& user, Dictionary& dictionary)
{
	if (user.newWord.length() != 0 && FindTranslation(dictionary, user.prevWord).size() == 0)
	{
		dictionary.dict.emplace(user.prevWord, user.newWord);
		dictionary.changed = true;
		std::cout << "Translation for \"" << user.prevWord << "\" added." << std::endl;
		std::cout << "Write the next word or press \"...\" to exit." << std::endl;
	}
}

void SaveDictionary(const Dictionary& dictionary, bool needSaving)
{
	std::cout << "The dictionary was changed. Would you like to save changes? (y/Y)" << std::endl;
	char save = std::cin.get();
	if (save == 'y' || save == 'Y' || needSaving)
	{
		std::ofstream newFile;
		newFile.open(dictionary.fileName, std::ios::trunc);
		for (auto it = dictionary.dict.begin(); it != dictionary.dict.end(); ++it)
		{
			newFile << (*it).first << " " << (*it).second << "\n";
		}
		std::cout << "Dictionary has saved in file " << dictionary.fileName << std::endl;
	}
}
