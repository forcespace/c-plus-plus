#include "CCar.h"

bool CCar::TurnOnEngine()
{
	if (m_isEngineOn)
	{
		return false;
	}
	else
	{
		m_isEngineOn = true;
		return true;
	}
}

bool CCar::TurnOffEngine()
{
	if (m_isEngineOn && m_gear == 0 && m_speed == 0)
	{
		m_isEngineOn = false;
		return true;
	}
	else
	{
		return false;
	}
}

bool CCar::SetGear(int gear)
{
	if (gear < GEAR_MIN || 
		gear > GEAR_MAX ||
		!m_isEngineOn && gear != 0 ||
		gear == -1 && m_speed != 0 ||
		m_gear == -1 && gear == 1 && m_speed != 0 ||
		!IsValidSpeedForGear(m_speed, gear))
		return false;

	m_gear = gear;
	return true;
}

bool CCar::SetSpeed(int speed)
{
	if (m_gear == 0 && speed > m_speed ||
		!IsValidSpeedForGear(speed, m_gear))
		return false;

	m_speed = speed;
	return true;
}

void CCar::GetInfo()
{
	std::cout << "  Engine: " << ((m_isEngineOn) ? "On" : "Off") << std::endl;
	std::cout << "  Direction: " << GetStringDirection() << std::endl;
	std::cout << "  Speed: " << m_speed << std::endl;
	std::cout << "  Gear: " << m_gear << std::endl;
}

int CCar::GetGear() const
{
	return m_gear;
}

int CCar::GetSpeed() const
{
	return m_speed;
}

bool CCar::IsValidSpeedForGear(const int speed, const int gear)
{
	if (gear < GEAR_MIN || gear > GEAR_MAX)
	{
		return false;
	}

	auto [speedMin, speedMax] = SPEED_RANGES[gear + 1];
	return speed >= speedMin && speed <= speedMax;
}

std::string CCar::GetStringDirection()
{
	if (m_speed == 0)
		return "In Place";
	else if (m_gear > 0)
		return "Forward";
	else if (m_gear == -1)
		return "Back";
	else 
		return "Unknown";
}
