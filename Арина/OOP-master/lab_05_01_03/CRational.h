#pragma once
#include <utility>

class CRational
{
public:
	CRational();
	CRational(int value);
	CRational(int numerator, int denominator);

	int GetNumerator() const;
	int GetDenominator() const;
	double ToDouble() const;
	std::pair<int, CRational> ToCompoundFraction() const;

	CRational const operator+() const;
	CRational const operator-() const;

	CRational const operator+(const CRational& rational);
	CRational const operator-(const CRational& rational);

    CRational& operator+=(const CRational& rational);
	CRational& operator+=(int number);
	CRational& operator-=(const CRational& rational);
	CRational& operator-=(int number);

	CRational const operator*(const CRational& rational);
	CRational const operator/(const CRational& rational);

	CRational& operator*=(const CRational& rational);
	CRational& operator*=(int number);
	CRational& operator/=(const CRational& rational);
	CRational& operator/=(int number);

	bool const operator==(const CRational& rational) const;
	bool const operator!=(const CRational& rational) const;

	bool const operator<(const CRational& rational) const;
	bool const operator>(const CRational& rational) const;
	bool const operator<=(const CRational& rational) const;
	bool const operator>=(const CRational& rational) const;

private:
	int m_numerator;
	int m_denominator;

	int GetNOD(int a, int b);
	int GetNOK(int a, int b) const;

	void NormalizeRational(int& numerator, int& denominator);
	bool IsIntOverflow(const long number);
};

CRational const operator+(int lhs, CRational& rhs);
CRational const operator+(CRational& lhs, int rhs);

CRational const operator-(int lhs, CRational& rhs);
CRational const operator-(CRational& lhs, int rhs);

CRational const operator*(int lhs, CRational& rhs);
CRational const operator*(CRational& lhs, int rhs);

CRational const operator/(int lhs, CRational& rhs);
CRational const operator/(CRational& lhs, int rhs);

bool const operator==(int lhs, const CRational& rhs);
bool const operator==(const CRational& lhs, int rhs);
bool const operator!=(int lhs, const CRational& rhs);
bool const operator!=(const CRational& lhs, int rhs);

bool const operator<(int lhs, const CRational& rhs);
bool const operator<(const CRational& lhs, int rhs);
bool const operator>(int lhs, const CRational& rhs);
bool const operator>(const CRational& lhs, int rhs);
bool const operator<=(int lhs, const CRational& rhs);
bool const operator<=(const CRational& lhs, int rhs);
bool const operator>=(int lhs, const CRational& rhs);
bool const operator>=(const CRational& lhs, int rhs);