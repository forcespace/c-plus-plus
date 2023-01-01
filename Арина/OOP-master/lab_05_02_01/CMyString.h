#pragma once
#include <string>

constexpr char nullCh = 0;

class CMyString
{
public:
	CMyString();
	CMyString(const char* pString);
	CMyString(const char* pString, size_t length);
	CMyString(CMyString const& other);
	CMyString(CMyString&& other);
	CMyString(std::string const& stlString);
	~CMyString();

	size_t GetLength() const;
	char* GetStringData() const;
	CMyString SubString(size_t start, size_t length = SIZE_MAX) const;
	void Clear();

	CMyString& operator=(const CMyString& other);
	CMyString const operator+(const CMyString& other);
	CMyString& operator+=(const CMyString& other);
	bool const operator==(const CMyString& other) const;
	bool const operator!=(const CMyString& other) const;
	const char& operator[](size_t id) const;
	char& operator[](size_t id);

private:
	size_t m_len;
	char* m_str;
};

CMyString const operator+(const std::string& lhs, const CMyString& rhs);
CMyString const operator+(const char* lhs, const CMyString& rhs);

