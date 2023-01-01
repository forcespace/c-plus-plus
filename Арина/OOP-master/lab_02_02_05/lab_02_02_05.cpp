#include "HtmlDecode.h"

int main()
{
	std::string htmlStr;
	while (std::getline(std::cin, htmlStr))
	{
		std::cout << HtmlDecode(htmlStr) << std::endl;
	}
	return 0;
}