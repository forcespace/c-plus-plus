#include "CHttpUrl.h"
#include "CUrlParsingError.h"
#include <regex>
#include <map>
#include <boost/algorithm/string.hpp>

const std::string URL_REGEX = "^(?:(http|https|ftp)?:\/\/)?([^\/@: ]+)(?::([0-9]{1,5}))?([^ ]*)?";
const unsigned short PORT_MIN = 1;
const unsigned short PORT_MAX = 65535;
const std::map <std::string, Protocol> protocolMap = {
    { "http",  Protocol::HTTP  },
    { "https", Protocol::HTTPS },
};
const std::map <Protocol, unsigned short> portMap = {
	{ Protocol::HTTP,  80  },
	{ Protocol::HTTPS, 443 },
};

CHttpUrl::CHttpUrl(std::string const& url)
{
	ParseUrl(url);
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol)
	: m_protocol(protocol)
{
	if (domain.empty())
	{
		throw CUrlParsingError("Empty domain.");
	}
	m_domain = domain;
	if (document.empty())
	{
		throw CUrlParsingError("Empty document.");
	}
	m_document = document[0] != '/' ? '/' + document : document;
	m_port = portMap.at(protocol);
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol, unsigned short port)
	: m_protocol(protocol)
{
	if (domain.empty())
	{
		throw CUrlParsingError("Empty domain.");
	}
	m_domain = domain;
	if (document.empty())
	{
		throw CUrlParsingError("Empty document.");
	}
	m_document = document[0] != '/' ? '/' + document : document;
	m_port = ParsePort(std::to_string(port), protocol);
}

std::string CHttpUrl::GetURL() const
{
	return std::string();
}

std::string CHttpUrl::GetDomain() const
{
	return m_domain;
}

std::string CHttpUrl::GetDocument() const
{
	return m_document;
}

Protocol CHttpUrl::GetProtocol() const
{
	return m_protocol;
}

unsigned short CHttpUrl::GetPort() const
{
	return m_port;
}

void CHttpUrl::ParseUrl(std::string const& url)
{
	std::smatch matches;
	std::regex  urlRegex(URL_REGEX);

	if (std::regex_search(url, matches, urlRegex))
	{
		m_protocol = ParseProtocol(matches[1]);
		m_domain = matches[2];
		m_port = ParsePort(matches[3], m_protocol);
		m_document = matches[4];
	}
}

Protocol CHttpUrl::ParseProtocol(std::string const& protocol)
{
	const std::string protocolLower = boost::algorithm::to_lower_copy(protocol);
	try
	{
		const Protocol protocolEnum = protocolMap.at(protocolLower);
		return protocolEnum;
	}
	catch(const std::exception&)
	{
		throw CUrlParsingError("Invalid protocol value. Protocol value should be equal to http or https.");
	}
}

unsigned short CHttpUrl::ParsePort(std::string const& port, Protocol const& protocol)
{
	if (port.empty())
	{
		return portMap.at(protocol);
	}

	try
	{
		unsigned short result = std::stoi(port);
		if (result >= PORT_MIN && result <= PORT_MAX)
		{
			return result;
		}
		else
		{
			throw CUrlParsingError("Invalid port value. Port value should be between 1 and 65535.");
		}
	}
	catch (std::invalid_argument)
	{
		throw CUrlParsingError("Invalid port value. Port value should be between 1 and 65535.");
	}
}

std::string CHttpUrl::GetUrlDocument(std::string const& document)
{
	return std::string();
}
