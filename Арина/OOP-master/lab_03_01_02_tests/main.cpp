#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>

#include "../lab_03_01_02/CCar.h"

SCENARIO("TurnOnEngine")
{
	WHEN("Engine was off")
	{
		CCar car;
		THEN("true")
		{
			CHECK(car.TurnOnEngine() == true);
		}
	}
	WHEN("Engine was on")
	{
		CCar car;
		car.TurnOnEngine();
		THEN("false")
		{
			CHECK(car.TurnOnEngine() == false);
		}
	}
}

SCENARIO("TurnOffEngine")
{
	WHEN("Engine was off")
	{
		CCar car;
		THEN("false")
		{
			CHECK(car.TurnOffEngine() == false);
		}
	}
	WHEN("Engine was on")
	{
		CCar car;
		car.TurnOnEngine();
		THEN("true")
		{
			CHECK(car.TurnOffEngine() == true);
		}
	}
	WHEN("Engine was on, gear is not neutral")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(1);
		THEN("false")
		{
			CHECK(car.TurnOffEngine() == false);
		}
	}
	WHEN("Engine was on, speed is not 0")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(10);
		THEN("false")
		{
			CHECK(car.TurnOffEngine() == false);
		}
	}
}

SCENARIO("SetGear")
{
	WHEN("Engine was off, gear changes to neutral")
	{
		CCar car;
		THEN("true")
		{
			CHECK(car.SetGear(0) == true);
		}
	}
	WHEN("Engine was off, gear changes not to neutral")
	{
		CCar car;
		THEN("false")
		{
			CHECK(car.SetGear(1) == false);
		}
	}
	WHEN("Engine was on, gear changes with valid speed")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(20);
		THEN("true")
		{
			CHECK(car.SetGear(2) == true);
		}
	}
	WHEN("Engine was on, gear changes with invalid speed")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(10);
		THEN("false")
		{
			CHECK(car.SetGear(2) == false);
		}
	}
	WHEN("Engine was on, gear changes to back with 0 speed")
	{
		CCar car;
		car.TurnOnEngine();
		THEN("true")
		{
			CHECK(car.SetGear(-1) == true);
		}
	}
	WHEN("Engine was on, gear changes to back with not 0 speed")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(10);
		THEN("false")
		{
			CHECK(car.SetGear(-1) == false);
		}
	}
}

SCENARIO("SetSpeed")
{
	WHEN("Engine was off")
	{
		CCar car;
		THEN("false")
		{
			CHECK(car.SetSpeed(20) == false);
		}
	}
	WHEN("Engine was on, gear is neutral")
	{
		CCar car;
		car.TurnOnEngine();
		THEN("false")
		{
			CHECK(car.SetSpeed(20) == false);
		}
	}
	WHEN("Engine was on, gear is first, speed is valid")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(1);
		THEN("true")
		{
			CHECK(car.SetSpeed(20) == true);
		}
	}
	WHEN("Engine was on, gear is first, speed is invalid")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(1);
		THEN("false")
		{
			CHECK(car.SetSpeed(40) == false);
		}
	}
}