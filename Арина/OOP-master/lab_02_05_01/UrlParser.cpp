#include "UrlParser.h"

const std::string URL_REGEX = "^((http|https|ftp)?:\/\/)?([^\/@: ]+)(:([0-9]{1,5}))?([^ ]*)?";

std::optional<Args> GetUrlFromInput(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Invalid arguments count." << std::endl;
		std::cout << "Usage: lab_02_05_01.exe <your url>." << std::endl;
		return std::nullopt;
	}
	Args url;
	try
	{
		url.value = argv[1];
		return url;
	}
	catch (const std::exception&)
	{
		return std::nullopt;
	}
}

bool ParseURL(std::string const& url, Protocol& protocol, int& port, std::string& host, std::string& document)
{
	std::smatch matches;
	std::regex  urlRegex(URL_REGEX);

	if (std::regex_search(url, matches, urlRegex)) 
	{
		protocol = GetProtocol(matches.str(2));
		port = GetPort(matches.str(5), protocol);
		host = matches.str(3);
		document = matches.str(6);
		return true;
	}
	else
	{
		return false;
	}
}

Protocol GetProtocol(std::string const& protocol)
{
	const std::map <std::string, Protocol> protocolMap = {
		{ "http",  Protocol::HTTP  },
		{ "https", Protocol::HTTPS },
		{ "ftp",   Protocol::FTP   }
	};

	const std::string protocolLower = boost::algorithm::to_lower_copy(protocol);
	auto it = protocolMap.find(protocolLower);
	const Protocol protocolEnum = (it != protocolMap.end()) ? it->second : Protocol::HTTP;
	return protocolEnum;
}

int GetPort(std::string const& port, Protocol const& protocol)
{
	const std::map <Protocol, int> protocolMap = {
		{ Protocol::HTTP,  80  },
		{ Protocol::HTTPS, 443 },
		{ Protocol::FTP,   21  }
	};
	int number;

	try
	{
		number = std::stoul(port);
	}
	catch (const std::exception&)
	{
		number = protocolMap.find(protocol)->second;
	}
	return number;
}