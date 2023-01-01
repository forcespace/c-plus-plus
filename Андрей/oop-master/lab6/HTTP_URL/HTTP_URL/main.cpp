#include "CHttpUrl.h"
#include "CUrlParsingError.h"
#include "common_libs.h"

int main()
{
	std::string line;
	while (getline(std::cin, line))
	{
		try
		{
			CHttpUrl url(line);

			std::cout << "url: " << url.GetURL() << std::endl;
			std::cout << "Protocol: " << CHttpUrl::FromProtocolToString(url.GetProtocol()) << std::endl;
			std::cout << "Domain: " << url.GetDomain() << std::endl;
			std::cout << "Port: " << url.GetPort() << std::endl;
			std::cout << "Document: " << url.GetDocument() << std::endl;
		}
		catch (const CUrlParsingError& error)
		{
			std::cout << error.what() << std::endl;
		}
		catch (const std::runtime_error& error)
		{
			std::cout << error.what() << std::endl;
		}
	}

	return 0;
}