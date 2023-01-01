#include "UrlParser.h"

int main(int argc, char* argv[])
{
	auto url = GetUrlFromInput(argc, argv);
	if (!url)
	{
		return 1;
	}

	std::cout << "Parsing entered URL." << std::endl;
	Protocol protocol;
	int port;
	std::string host;
	std::string document;
	if (ParseURL(url->value, protocol, port, host, document))
	{
		std::cout << "URL:  " << url->value << std::endl;
		std::cout << "HOST: " << host << std::endl;
		std::cout << "PORT: " << port << std::endl;
		std::cout << "DOC:  " << document << std::endl;
	}
	else
	{
		std::cout << "Invalid URL!" << std::endl;
	}
	return 0;
}