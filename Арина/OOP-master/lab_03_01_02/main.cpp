#include "CCar.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <boost/algorithm/string.hpp>

enum class CommandTypes
{
	EngineOn,
	EngineOff,
	Info,
	SetGear,
	SetSpeed
};

const std::map <std::string, CommandTypes> commandMap = {
	{ "engineon",  CommandTypes::EngineOn  },
	{ "engineoff", CommandTypes::EngineOff },
	{ "info",      CommandTypes::Info      },
	{ "setgear",   CommandTypes::SetGear   },
	{ "setspeed",  CommandTypes::SetSpeed  },
};

int main()
{
	CCar car;
	std::string line;
	std::vector<std::string> command;

	std::cout << "Enter command:" << std::endl;

	while (std::getline(std::cin, line))
	{
		boost::algorithm::to_lower(line);
		boost::split(command, line, [](char c) {return c == ' '; });
		auto it = commandMap.find(command[0]);
		if (it == commandMap.end()) continue;
		switch (it->second)
		{
		case CommandTypes::EngineOn:
		{
			car.TurnOnEngine();
			break;
		}
		case CommandTypes::EngineOff:
		{
			car.TurnOffEngine();
			break;
		}
		case CommandTypes::Info:
		{
			car.GetInfo();
			break;
		}
		case CommandTypes::SetGear:
		{
			try
			{
				car.SetGear(std::stoi(command[1]));
			}
			catch (const std::exception&)
			{
				std::cout << "Invalid gear parameter." << std::endl;
			}
			break;
		}
		case CommandTypes::SetSpeed:
		{
			try
			{
				car.SetSpeed(std::stoi(command[1]));
			}
			catch (const std::exception&)
			{
				std::cout << "Invalid speed parameter." << std::endl;
			}
			break;
		}
		default:
		{
			std::cout << "Unknow command." << std::endl;
			break;
		}
		}
	}

	return 0;
}