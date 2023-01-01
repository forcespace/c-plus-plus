#include "CHttpUrl.h"
#include "CUrlParsingError.h"

#include "common_libs.h"

CHttpUrl::CHttpUrl(const std::string& url)
{
	try
	{
		ParseURL(url);
	}
	catch (const std::exception& error)
	{
		throw CUrlParsingError(error.what());
	}
}

CHttpUrl::CHttpUrl(const std::string& domain, const std::string& document, Protocol protocol)
	: CHttpUrl(domain, document, protocol, GetDefaultPort(protocol))
{
}

CHttpUrl::CHttpUrl(const std::string& domain, const std::string& document, Protocol protocol, unsigned short port)
{
	if (domain.empty())
	{
		throw CUrlParsingError(CHttpUrl::ERROR_WRONG_URL);
	}

	if (port < 1 || port > USHRT_MAX)
	{
		throw CUrlParsingError(CHttpUrl::ERROR_WRONG_PORT);
	}

	m_domain = domain;
	m_document = ParseDocument(document);
	m_protocol = protocol;
	m_port = port;
}

std::string CHttpUrl::GetURL() const
{
	std::string url = m_protocol == Protocol::HTTP ? "http" : "https";

	url += "://";
	url += m_domain == "/" ? "" : m_domain;
	url += m_port == DefaultPorts.find(m_protocol)->second ? "" : ":" + std::to_string(m_port);
	url += m_document;

	return url;
}

std::string CHttpUrl::GetDomain() const
{
	return m_domain;
}

std::string CHttpUrl::GetDocument() const
{
	return m_document;
}

unsigned short CHttpUrl::GetPort() const
{
	return m_port;
}

Protocol CHttpUrl::GetProtocol() const
{
	return m_protocol;
}

void CHttpUrl::ParseURL(const std::string& url)
{
	std::regex regex("^((http[s]?)://)?([-.[:alnum:]]+)(:([[:digit:]]+))?(/(.*))?$", std::regex_constants::icase);
	std::smatch matches;
	std::regex_search(url, matches, regex);

	if (matches.empty())
	{
		throw std::invalid_argument(CHttpUrl::ERROR_WRONG_URL);
	}

	this->m_protocol = ParseProtocol(matches[2]);
	this->m_domain = matches[3];
	this->m_port = ParsePort(matches[5], m_protocol);
	this->m_document = ParseDocument(matches[7]);
}

std::string CHttpUrl::ParseDocument(const std::string& document)
{
	if (document.empty() || document[0] != '/')
	{
		return "/" + document;
	}

	return document;
}

Protocol CHttpUrl::ParseProtocol(const std::string& protocol)
{
	if (CHttpUrl::GetStringInLowerCase(protocol) == "https")
	{
		return Protocol::HTTPS;
	}

	return Protocol::HTTP;
}

unsigned short CHttpUrl::ParsePort(const std::string& port, const Protocol& protocol)
{
	if (port.empty())
	{
		return GetDefaultPort(protocol);
	}

	auto numPort = static_cast<unsigned int>(std::stoi(port));

	if (numPort > USHRT_MAX || numPort < 1)
	{
		throw std::invalid_argument(CHttpUrl::ERROR_WRONG_PORT);
	}

	return static_cast<int>(numPort);
}

unsigned short CHttpUrl::GetDefaultPort(const Protocol& protocol)
{
	auto it = DefaultPorts.find(protocol);

	if (it == DefaultPorts.end())
	{
		throw std::runtime_error(CHttpUrl::ERROR_WRONG_PROTOCOL);
	}

	return it->second;
}

std::string CHttpUrl::FromProtocolToString(const Protocol& protocol)
{
	if (protocol == Protocol::HTTP)
	{
		return "http";
	}

	return "https";
}

std::string CHttpUrl::GetStringInLowerCase(const std::string& line)
{
	std::string stringInLowerCase;
	for (auto element : line)
	{
		stringInLowerCase += tolower(element);
	}

	return stringInLowerCase;
}