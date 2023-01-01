#pragma once
#include <string>

enum Protocol
{
	HTTP,
	HTTPS
};


class CHttpUrl
{
public:
	CHttpUrl(std::string const& url);
	CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol = HTTP);
	CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol, unsigned short port);

	std::string GetURL() const;
	std::string GetDomain() const;
	std::string GetDocument() const;
	Protocol GetProtocol() const;
	unsigned short GetPort() const;

private:
	std::string m_domain;
	std::string m_document;
	Protocol m_protocol;
	unsigned short m_port;

	void ParseUrl(std::string const& url);
	Protocol ParseProtocol(std::string const& protocol);
	unsigned short ParsePort(std::string const& port, Protocol const& protocol);
	std::string GetUrlDocument(std::string const& document);
};

