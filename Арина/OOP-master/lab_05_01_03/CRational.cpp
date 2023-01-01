#include "CRational.h"
#include <limits>
#include <stdexcept>
#include <algorithm>
#include <cstdlib>

constexpr int intMin = std::numeric_limits<int>::min();
constexpr int intMax = std::numeric_limits<int>::max();

int CRational::GetNOD(int a, int b)
{
	while (b != 0)
	{
		std::swap(a, b);
		b = b % a;
	}
	return (a != 0) ? a : 1;
}

int CRational::GetNOK(int a, int b) const
{
	for (int i = std::max(std::abs(a), std::abs(b)); i > 0; i++)
	{
		if ((i % a == 0) && (i % b == 0))
		{
			return i;
		}
	}
}

void CRational::NormalizeRational(int& numerator, int& denominator)
{
	int nod = GetNOD(std::abs(numerator), denominator);
	if (nod > 1)
	{
		numerator /= nod;
		denominator /= nod;
	}
}

bool CRational::IsIntOverflow(const long number)
{
	return number < intMin || number > intMax;
}

CRational::CRational()
	: m_numerator(0)
	, m_denominator(1)
{}

CRational::CRational(int value)
	: m_numerator(value)
	, m_denominator(1)
{}

CRational::CRational(int numerator, int denominator)
{
	if (denominator == 0)
	{
		throw std::invalid_argument("denominator");
	}
	if (denominator < 0)
	{
		numerator *= -1;
		denominator = std::abs(denominator);
	}
	NormalizeRational(numerator, denominator);
	m_numerator = numerator;
	m_denominator = denominator;
}

double CRational::ToDouble() const
{
	return static_cast<double>(m_numerator) / m_denominator;
}

std::pair<int, CRational> CRational::ToCompoundFraction() const
{
	if (std::abs(m_numerator) < m_denominator)
	{
		return std::make_pair(0, *this);
	}
	else
	{
		const auto [quot, rem] = std::div(m_numerator, m_denominator);
		return std::make_pair(quot, CRational(rem, m_denominator));
	}
}

int CRational::GetNumerator() const
{
	return m_numerator;
}

int CRational::GetDenominator() const
{
	return m_denominator;
}

CRational const CRational::operator+() const
{
	return CRational(m_numerator, m_denominator);
}

CRational const CRational::operator-() const
{
	return CRational(-m_numerator, m_denominator);
}

CRational const CRational::operator+(const CRational& rational)
{
	int denominator = GetNOK(m_denominator, rational.m_denominator);
	int numerator = m_numerator * (denominator / m_denominator) + rational.GetNumerator() * (denominator / rational.GetDenominator());
	NormalizeRational(numerator, denominator);
	return CRational(numerator, denominator);
}

CRational const CRational::operator-(const CRational& rational)
{
	int denominator = GetNOK(m_denominator, rational.m_denominator);
	int numerator = m_numerator * (denominator / m_denominator) - rational.GetNumerator() * (denominator / rational.GetDenominator());
	NormalizeRational(numerator, denominator);
	return CRational(numerator, denominator);
}

CRational& CRational::operator+=(const CRational& rational)
{
	CRational tmp = *this + rational;
	m_numerator = tmp.GetNumerator();
	m_denominator = tmp.GetDenominator();
	return *this;
}

CRational& CRational::operator+=(int number)
{
	return *this += CRational(number);
}

CRational& CRational::operator-=(const CRational& rational)
{
	CRational tmp = *this - rational;
	m_numerator = tmp.GetNumerator();
	m_denominator = tmp.GetDenominator();
	return *this;
}

CRational& CRational::operator-=(int number)
{
	return *this -= CRational(number);
}

CRational const CRational::operator*(const CRational& rational)
{
	int numerator = m_numerator * rational.GetNumerator();
	int denominator = m_denominator * rational.GetDenominator();
	NormalizeRational(numerator, denominator);
	return CRational(numerator, denominator);
}

CRational const CRational::operator/(const CRational& rational)
{
	int numerator = m_numerator * rational.GetDenominator();
	int denominator = m_denominator * rational.GetNumerator();
	NormalizeRational(numerator, denominator);
	return CRational(numerator, denominator);
}

CRational& CRational::operator*=(const CRational& rational)
{
	CRational tmp = *this * rational;
	m_numerator = tmp.GetNumerator();
	m_denominator = tmp.GetDenominator();
	return *this;
}

CRational& CRational::operator*=(int number)
{
	return *this *= CRational(number);
}

CRational& CRational::operator/=(const CRational& rational)
{
	CRational tmp = *this / rational;
	m_numerator = tmp.GetNumerator();
	m_denominator = tmp.GetDenominator();
	return *this;
}

CRational& CRational::operator/=(int number)
{
	return *this /= CRational(number);
}

bool const CRational::operator==(const CRational& rational) const
{
	return m_numerator == rational.GetNumerator() && m_denominator == rational.GetDenominator();
}

bool const CRational::operator!=(const CRational& rational) const
{
	return m_numerator != rational.GetNumerator() || m_denominator != rational.GetDenominator();
}

bool const CRational::operator<(const CRational& rational) const
{
	int denominator = GetNOK(m_denominator, rational.m_denominator);
	return m_numerator * (denominator / m_denominator) < rational.GetNumerator() * (denominator / rational.GetDenominator());
}

bool const CRational::operator>(const CRational& rational) const
{
	int denominator = GetNOK(m_denominator, rational.m_denominator);
	return m_numerator * (denominator / m_denominator) > rational.GetNumerator() * (denominator / rational.GetDenominator());
}

bool const CRational::operator<=(const CRational& rational) const
{
	int denominator = GetNOK(m_denominator, rational.m_denominator);
	return m_numerator * (denominator / m_denominator) <= rational.GetNumerator() * (denominator / rational.GetDenominator());
}

bool const CRational::operator>=(const CRational& rational) const
{
	int denominator = GetNOK(m_denominator, rational.m_denominator);
	return m_numerator * (denominator / m_denominator) >= rational.GetNumerator() * (denominator / rational.GetDenominator());
}

CRational const operator+(int lhs, CRational& rhs)
{
	return CRational(lhs) + rhs;
}

CRational const operator+(CRational& lhs, int rhs)
{
	return lhs + CRational(rhs);
}

CRational const operator-(int lhs, CRational& rhs)
{
	return CRational(lhs) - rhs;
}

CRational const operator-(CRational& lhs, int rhs)
{
	return lhs - CRational(rhs);
}

CRational const operator*(int lhs, CRational& rhs)
{
	return CRational(lhs) * rhs;
}

CRational const operator*(CRational& lhs, int rhs)
{
	return lhs * CRational(rhs);
}

CRational const operator/(int lhs, CRational& rhs)
{
	return CRational(lhs) / rhs;
}

CRational const operator/(CRational& lhs, int rhs)
{
	return lhs / CRational(rhs);
}

bool const operator==(int lhs, const CRational& rhs)
{
	return CRational(lhs) == rhs;
}

bool const operator==(const CRational& lhs, int rhs)
{
	return lhs == CRational(rhs);
}

bool const operator!=(int lhs, const CRational& rhs)
{
	return CRational(lhs) != rhs;
}

bool const operator!=(const CRational& lhs, int rhs)
{
	return lhs != CRational(rhs);
}

bool const operator<(int lhs, const CRational& rhs)
{
	return CRational(lhs) < rhs;
}

bool const operator<(const CRational& lhs, int rhs)
{
	return lhs < CRational(rhs);
}

bool const operator>(int lhs, const CRational& rhs)
{
	return CRational(lhs) > rhs;
}

bool const operator>(const CRational& lhs, int rhs)
{
	return lhs > CRational(rhs);
}

bool const operator<=(int lhs, const CRational& rhs)
{
	return CRational(lhs) <= rhs;
}

bool const operator<=(const CRational& lhs, int rhs)
{
	return lhs <= CRational(rhs);
}

bool const operator>=(int lhs, const CRational& rhs)
{
	return CRational(lhs) >= rhs;
}

bool const operator>=(const CRational& lhs, int rhs)
{
	return lhs >= CRational(rhs);
}
