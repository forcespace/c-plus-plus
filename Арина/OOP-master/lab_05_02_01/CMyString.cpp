#include "CMyString.h"
#include <algorithm>
#include <stdexcept>

CMyString::CMyString()
	: m_len(0)
{
	m_str = new char[m_len + 1];
	m_str[0] = nullCh;
}

CMyString::CMyString(const char* pString)
	: CMyString(pString, std::strlen(pString))
{
}

CMyString::CMyString(const char* pString, size_t length)
	: m_len(length)
{
	m_str = new char[m_len + 1];
	std::memcpy(m_str, pString, length);
	m_str[m_len] = nullCh;
}

CMyString::CMyString(CMyString const& other)
	: CMyString(other.GetStringData(), other.GetLength())
{
}

CMyString::CMyString(CMyString&& other)
	: m_str(other.GetStringData())
	, m_len(other.GetLength())
{
	other.m_str = nullptr;
	other.m_len = 0;
}

CMyString::CMyString(std::string const& stlString)
	: CMyString(stlString.c_str(), stlString.length())
{
}

CMyString::~CMyString()
{
	delete[] m_str;
}

size_t CMyString::GetLength() const
{
	return m_len;
}

char* CMyString::GetStringData() const
{
	return m_str;
}

CMyString CMyString::SubString(size_t start, size_t length) const
{
	if (start > m_len)
	{
		throw std::out_of_range("Out of range.");
	}
	return CMyString(m_str + start, std::min(m_len - start, length));
}

void CMyString::Clear()
{
	delete[] m_str;
	m_len = 0;
	m_str = new char[m_len + 1];
	m_str[m_len] = nullCh;
}

CMyString& CMyString::operator=(const CMyString& other)
{
	if (this != &other)
	{
		CMyString tmp(other);
		std::swap(m_str, tmp.m_str);
		std::swap(m_len, tmp.m_len);
	}

	return *this;
}

CMyString const CMyString::operator+(const CMyString& other)
{
	size_t length = m_len + other.GetLength();
	char* pString = new char[length + 1];
	std::memcpy(pString, m_str, m_len);
	std::memcpy(pString + m_len, other.GetStringData(), other.GetLength());
	pString[length] = '\0';
	CMyString newMyString(pString, length);
	delete[] pString;
	return newMyString;
}

CMyString& CMyString::operator+=(const CMyString& other)
{
	*this = *this + other;
	return *this;
}

bool const CMyString::operator==(const CMyString& other) const
{
	return m_len == other.GetLength() && std::strcmp(m_str, other.GetStringData()) == 0;
}

bool const CMyString::operator!=(const CMyString& other) const
{
	return !(*this == other);
}

const char& CMyString::operator[](size_t id) const
{
	if (id > m_len)
	{
		throw std::out_of_range("Out of range.");
	}
	return m_str[id];
}

char& CMyString::operator[](size_t id)
{
	if (id > m_len)
	{
		throw std::out_of_range("Out of range.");
	}
	return m_str[id];
}

CMyString const operator+(const std::string& lhs, const CMyString& rhs)
{
	return CMyString(lhs) + rhs;
}

CMyString const operator+(const char* lhs, const CMyString& rhs)
{
	return CMyString(lhs) + rhs;
}
