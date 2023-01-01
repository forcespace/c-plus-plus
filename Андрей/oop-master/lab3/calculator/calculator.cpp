#include "common_libs.h"
#include "CCalculator.h"
#include "CRemoteController.h"

int main()
{
	CCalculator calculator;
	CRemoteController remoteController(calculator, std::cin, std::cout);
	while (!std::cin.eof() && !std::cin.fail())
	{
		std::cout << "> ";
		if (!remoteController.HandleCommand())
		{
			std::cout << "There are some problems with your command. Please, run command <help>" << std::endl;
		}
	}

	return 0;
}
