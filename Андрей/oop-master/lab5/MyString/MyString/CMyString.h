#pragma once
#include "common_libs.h"

class CMyString
{
public:
	CMyString();

	CMyString(const char* pString);

	CMyString(const char* pString, size_t length);

	CMyString(const CMyString& string);

	CMyString(CMyString&& string);

	CMyString(std::string const& stlString);

	size_t GetLength() const;

	const char* GetStringData() const;

	CMyString GetSubString(size_t start, size_t length = SIZE_MAX) const;

	CMyString& operator=(const CMyString& string);

	CMyString& operator=(CMyString&& string);

	CMyString& operator+=(const CMyString& string);

	const char& operator[](size_t index) const;

	char& operator[](size_t index);

	friend CMyString operator+(const CMyString& firstString, const CMyString& secondString);

	friend bool operator==(const CMyString& firstString, const CMyString& secondString);

	friend bool operator<(const CMyString& firstString, const CMyString& secondString);
	
	friend bool operator<=(const CMyString& firstString, const CMyString& secondString);

	friend bool operator>(const CMyString& firstString, const CMyString& secondString);

	friend bool operator>=(const CMyString& firstString, const CMyString& secondString);

	friend bool operator!=(const CMyString& firstString, const CMyString& secondString);
	
	friend std::istream& operator>>(std::istream& iss, CMyString& string);

	friend std::ostream& operator<<(std::ostream& oss, CMyString& string);

	~CMyString();

private:
	short static Compare(const CMyString& firstString, const CMyString& secondString);

	char* m_string;

	size_t m_length;

	inline static const char m_empty[1] = { '\0' };
};
