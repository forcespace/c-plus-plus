#include "CMyString.h"
#include "common_libs.h"

CMyString::CMyString()
{
	m_length = 0;
	m_string = new char[m_length + 1];

	m_string[m_length] = '\0';
}

CMyString::~CMyString()
{
	delete[] m_string;
}

CMyString::CMyString(const char* pString)
{
	m_length = strlen(pString);
	m_string = new char[m_length + 1];

	std::memcpy(m_string, pString, m_length);
	m_string[m_length] = '\0';
}

CMyString::CMyString(const char* pString, size_t length)
{
	m_length = length;
	m_string = new char[m_length + 1];

	std::memcpy(m_string, pString, m_length);
	m_string[m_length] = '\0';
}

CMyString::CMyString(const CMyString& string)
{
	m_length = string.m_length;
	m_string = new char[m_length + 1];
	auto tempString = string.GetStringData();

	std::memcpy(m_string, tempString, m_length);
	m_string[m_length] = '\0';
}

CMyString::CMyString(CMyString&& string)
{
	m_string = string.m_string;
	m_length = string.m_length;

	string.m_length = 0;
	string.m_string = nullptr;
}

CMyString::CMyString(const std::string& stlString)
{
	m_length = std::size(stlString);
	m_string = new char[m_length + 1];

	std::memcpy(m_string, stlString.c_str(), m_length);
	m_string[m_length] = '\0';
}

CMyString& CMyString::operator=(const CMyString& string)
{
	if (this == &string)
	{
		return *this;
	}

	char* tempString = new char[string.m_length + 1];

	delete[] m_string;

	std::memcpy(tempString, string.GetStringData(), string.m_length);
	m_length = string.m_length;
	
	m_string = tempString;

	m_string[m_length] = '\0';

	return *this;
}

CMyString& CMyString::operator=(CMyString&& string)
{
	*this = string;

	string.m_string = nullptr;

	return *this;
}

CMyString CMyString::GetSubString(size_t start, size_t length) const
{
	if (m_length < start)
	{
		throw std::invalid_argument("Wrong params");
	}

	length = length + start < m_length ? length : m_length - start;

	return CMyString(&(this->GetStringData())[start], length);
}

size_t CMyString::GetLength() const
{
	return m_length;
}

const char* CMyString::GetStringData() const
{
	if (m_string == nullptr)
	{
		return m_empty;
	}

	return m_string;
}

CMyString& CMyString::operator+=(const CMyString& string)
{
	*this = *this + string;

	return *this;
}

CMyString operator+(const CMyString& firstString, const CMyString& secondString)
{
	auto firstStringData = firstString.GetStringData();
	auto secondStringData = secondString.GetStringData();

	CMyString resultString("", firstString.m_length + secondString.m_length);
	
	std::memcpy(resultString.m_string, firstStringData, firstString.m_length);
	std::memcpy(&resultString.m_string[firstString.m_length], secondStringData, secondString.m_length);

	resultString.m_string[resultString.m_length] = '\0';

	return resultString;
}

bool operator==(const CMyString& firstString, const CMyString& secondString)
{
	auto result = CMyString::Compare(firstString, secondString);

	return result == 0;
}

bool operator<(const CMyString& firstString, const CMyString& secondString)
{
	auto result = CMyString::Compare(firstString, secondString);

	return result < 0;
}

bool operator>(const CMyString& firstString, const CMyString& secondString)
{
	auto result = CMyString::Compare(firstString, secondString);

	return result > 0;
}

short CMyString::Compare(const CMyString& firstString, const CMyString& secondString)
{
	auto minLength = std::min(firstString.m_length, secondString.m_length);

	int result = std::memcmp(firstString.GetStringData(), secondString.GetStringData(), minLength);

	if (result != 0)
	{
		return result;
	}

	if (minLength < firstString.m_length)
	{
		return 1;
	}

	if (minLength < secondString.m_length)
	{
		return -1;
	}

	return 0;
}

bool operator<=(const CMyString& firstString, const CMyString& secondString)
{
	auto result = CMyString::Compare(firstString, secondString);

	return result <= 0;
}

bool operator>=(const CMyString& firstString, const CMyString& secondString)
{
	auto result = CMyString::Compare(firstString, secondString);

	return result >= 0;
}

bool operator!=(const CMyString& firstString, const CMyString& secondString)
{
	return !(firstString == secondString);
}

std::istream& operator>>(std::istream& iss, CMyString& string)
{
	char charForReading = '.';

	std::string resultString;

	if (!iss.good() || iss.eof())
	{
		return iss;
	}

	iss.get(charForReading);
	do
	{
		resultString += charForReading;

	} while (iss.good() && !iss.eof() && iss.get(charForReading));

	string = resultString;

	return iss;
}

const char& CMyString::operator[](size_t index) const
{
	if (index > m_length)
	{
		throw std::invalid_argument("Index out of range");
	}

	return m_string[index];
}

char& CMyString::operator[](size_t index)
{
	if (index > m_length)
	{
		throw std::invalid_argument("Index out of range");
	}

	return m_string[index];
}

std::ostream& operator<<(std::ostream& oss, CMyString& string)
{
	for (size_t i = 0; i < string.GetLength(); i++)
	{
		oss << string.m_string[i];
	}

	return oss;
}
