#pragma once
class CPoint
{
public:
	CPoint(double x = 0, double y = 0)
		: m_x(x)
		, m_y(y)
	{
	}
	double x() const;
	double y() const;

private:
	double m_x = 0;
	double m_y = 0;
};

