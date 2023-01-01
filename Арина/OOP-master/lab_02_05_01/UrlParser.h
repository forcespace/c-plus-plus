#pragma once
#include <optional>
#include <iostream>
#include <string>
#include <regex>
#include <map>
#include <boost/algorithm/string.hpp>

struct Args
{
	std::string value;
};

enum class Protocol
{
	HTTP,
	HTTPS,
	FTP
};

std::optional<Args> GetUrlFromInput(int argc, char* argv[]);
bool ParseURL(std::string const& url, Protocol& protocol, int& port, std::string& host, std::string& document);
Protocol GetProtocol(std::string const& protocol);
int GetPort(std::string const& port, Protocol const& protocol);