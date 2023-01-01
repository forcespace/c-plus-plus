#include "Dictionary.h"

int main(int argc, char* argv[])
{
	std::cout << "Translates words from Russian into English and vice versa.\n";
	std::cout << "Input <word> to translate or '...' to exit." << std::endl;

	Dictionary dictionary;
	dictionary.fileName = *GetDictionaryFileName(argc, argv);
	dictionary.dict = GetDictionaryFromFile(dictionary.fileName);

	if (Translation(dictionary))
	{
		SaveDictionary(dictionary);
	}

	std::cout << "Thanks for using!" << std::endl;

	return 0;
}