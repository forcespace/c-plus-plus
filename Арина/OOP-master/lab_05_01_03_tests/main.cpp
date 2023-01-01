#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>
#include <limits>
#include <utility>
#include <cstdlib>
#include "../lab_05_01_03/CRational.h"

constexpr int intMin = std::numeric_limits<int>::min();
constexpr int intMax = std::numeric_limits<int>::max();

SCENARIO("Creating rational")
{
	WHEN("()")
	{
		CRational r;
		THEN("Created")
		{
			CHECK(r.GetNumerator() == 0);
			CHECK(r.GetDenominator() == 1);
		}
	}
	WHEN("(int)")
	{
		CRational r(10);
		THEN("Created")
		{
			CHECK(r.GetNumerator() == 10);
			CHECK(r.GetDenominator() == 1);
		}
	}
	WHEN("(int, int)")
	{
		CRational r1(10, 5);
		THEN("Created")
		{
			CHECK(r1.GetNumerator() == 2);
			CHECK(r1.GetDenominator() == 1);
		}

		CRational r2(-10, 5);
		THEN("Created")
		{
			CHECK(r2.GetNumerator() == -2);
			CHECK(r2.GetDenominator() == 1);
		}

		CRational r3(-10, -5);
		THEN("Created")
		{
			CHECK(r3.GetNumerator() == 2);
			CHECK(r3.GetDenominator() == 1);
		}

		CRational r4(10, -5);
		THEN("Created")
		{
			CHECK(r4.GetNumerator() == -2);
			CHECK(r4.GetDenominator() == 1);
		}
	}
	WHEN("(int, int): denominator = 0")
	{
		REQUIRE_THROWS([]() {
			CRational r(10, 0);
		}());
	}
}

SCENARIO("ToDouble()")
{
	WHEN("(int)")
	{
		THEN("Ok")
		{
			CHECK(CRational(1).ToDouble() == 1);
		}
	}
	WHEN("(int, int)")
	{
		THEN("Ok")
		{
			CHECK(CRational(5, 10).ToDouble() == 0.5);
		}
	}
}

SCENARIO("ToCompoundFraction()")
{
	WHEN("(int)")
	{
		THEN("Ok")
		{
			const auto [a, b] = CRational(1).ToCompoundFraction();
			REQUIRE(a == 1);
			REQUIRE(b.GetNumerator() == 0);
			REQUIRE(b.GetDenominator() == 1);
		}
	}
	WHEN("(int)")
	{
		THEN("Ok")
		{
			const auto [a, b] = CRational(-1).ToCompoundFraction();
			REQUIRE(a == -1);
			REQUIRE(b.GetNumerator() == 0);
			REQUIRE(b.GetDenominator() == 1);
		}
	}
	WHEN("(int, int)")
	{
		THEN("Ok")
		{
			const auto [a, b] = CRational(3, 3).ToCompoundFraction();
			REQUIRE(a == 1);
			REQUIRE(b.GetNumerator() == 0);
			REQUIRE(b.GetDenominator() == 1);
		}
	}
	WHEN("(int, int)")
	{
		THEN("Ok")
		{
			const auto [a, b] = CRational(-3, 3).ToCompoundFraction();
			REQUIRE(a == -1);
			REQUIRE(b.GetNumerator() == 0);
			REQUIRE(b.GetDenominator() == 1);
		}
	}
	WHEN("(int, int)")
	{
		THEN("Ok")
		{
			const auto [a, b] = CRational(4, 3).ToCompoundFraction();
			REQUIRE(a == 1);
			REQUIRE(b.GetNumerator() == 1);
			REQUIRE(b.GetDenominator() == 3);
		}
	}
	WHEN("(int, int)")
	{
		THEN("Ok")
		{
			const auto [a, b] = CRational(-4, 3).ToCompoundFraction();
			REQUIRE(a == -1);
			REQUIRE(b.GetNumerator() == -1);
			REQUIRE(b.GetDenominator() == 3);
		}
	}
}

SCENARIO("Unary Operations")
{
	WHEN("+CRational")
	{
		CRational r(2, 5);
		CRational res = +r;
		THEN("Ok")
		{
			CHECK(res.GetNumerator() == 2);
			CHECK(res.GetDenominator() == 5);
		}
	}
	WHEN("-CRational")
	{
		CRational r(2, 5);
		CRational res = -r;
		THEN("Ok")
		{
			CHECK(res.GetNumerator() == -2);
			CHECK(res.GetDenominator() == 5);
		}
	}
}

SCENARIO("Operations +")
{
	WHEN("CRational + CRational")
	{
		THEN("Ok")
		{
			CRational r3(1, 2);
			CRational r4(1, 6);
			CRational res2 = r3 + r4;
			CHECK(res2.GetNumerator() == 2);
			CHECK(res2.GetDenominator() == 3);
		}
	}
	WHEN("Int + CRational")
	{
		THEN("Ok")
		{
			CRational r1(2, 5);
			CRational res1 = 2 + r1;
			CHECK(res1.GetNumerator() == 12);
			CHECK(res1.GetDenominator() == 5);
		}
	}
	WHEN("CRational + Int")
	{
		THEN("Ok")
		{
			CRational r1(2, 5);
			CRational res1 = r1 + 2;
			CHECK(res1.GetNumerator() == 12);
			CHECK(res1.GetDenominator() == 5);
		}
	}
	WHEN("CRational += CRational")
	{
		THEN("Ok")
		{
			CRational r3(1, 2);
			CRational r4(1, 6);
			CRational res2 = r3 += r4;
			CHECK(res2.GetNumerator() == 2);
			CHECK(res2.GetDenominator() == 3);
		}
	}
	WHEN("CRational += Int")
	{
		THEN("Ok")
		{
			CRational r1(2, 5);
			CRational res1 = r1 += 2;
			CHECK(res1.GetNumerator() == 12);
			CHECK(res1.GetDenominator() == 5);
		}
	}
}

SCENARIO("Operations -")
{
	WHEN("CRational - CRational")
	{
		THEN("Ok")
		{
			CRational r3(7, 10);
			CRational r4(2, 10);
			CRational res2 = r3 - r4;
			CHECK(res2.GetNumerator() == 1);
			CHECK(res2.GetDenominator() == 2);
		}
	}
	WHEN("Int - CRational")
	{
		THEN("Ok")
		{
			CRational r1(2, 5);
			CRational res1 = 2 - r1;
			CHECK(res1.GetNumerator() == 8);
			CHECK(res1.GetDenominator() == 5);
		}
	}
	WHEN("CRational - Int")
	{
		THEN("Ok")
		{
			CRational r1(8, 5);
			CRational res1 = r1 - 1;
			CHECK(res1.GetNumerator() == 3);
			CHECK(res1.GetDenominator() == 5);
		}
	}
	WHEN("CRational -= CRational")
	{
		THEN("Ok")
		{
			CRational r3(7, 10);
			CRational r4(2, 10);
			CRational res2 = r3 -= r4;
			CHECK(res2.GetNumerator() == 1);
			CHECK(res2.GetDenominator() == 2);
		}
	}
	WHEN("CRational -= Int")
	{
		THEN("Ok")
		{
			CRational r1(8, 5);
			CRational res1 = r1 -= 1;
			CHECK(res1.GetNumerator() == 3);
			CHECK(res1.GetDenominator() == 5);
		}
	}
}

SCENARIO("Operations *")
{
	WHEN("CRational * CRational")
	{
		THEN("Ok")
		{
			CRational r3(1, 2);
			CRational r4(1, 6);
			CRational res2 = r3 * r4;
			CHECK(res2.GetNumerator() == 1);
			CHECK(res2.GetDenominator() == 12);
		}
	}
	WHEN("Int * CRational")
	{
		THEN("Ok")
		{
			CRational r1(2, 5);
			CRational res1 = 2 * r1;
			CHECK(res1.GetNumerator() == 4);
			CHECK(res1.GetDenominator() == 5);
		}
	}
	WHEN("CRational * Int")
	{
		THEN("Ok")
		{
			CRational r1(2, 5);
			CRational res1 = r1 * 2;
			CHECK(res1.GetNumerator() == 4);
			CHECK(res1.GetDenominator() == 5);
		}
	}
	WHEN("CRational *= CRational")
	{
		THEN("Ok")
		{
			CRational r3(1, 2);
			CRational r4(1, 6);
			CRational res2 = r3 *= r4;
			CHECK(res2.GetNumerator() == 1);
			CHECK(res2.GetDenominator() == 12);
		}
	}
	WHEN("CRational *= Int")
	{
		THEN("Ok")
		{
			CRational r1(2, 5);
			CRational res1 = r1 *= 2;
			CHECK(res1.GetNumerator() == 4);
			CHECK(res1.GetDenominator() == 5);
		}
	}
}

SCENARIO("Operations /")
{
	WHEN("CRational / CRational")
	{
		THEN("Ok")
		{
			CRational r3(1, 2);
			CRational r4(1, 6);
			CRational res2 = r3 / r4;
			CHECK(res2.GetNumerator() == 3);
			CHECK(res2.GetDenominator() == 1);
		}
	}
	WHEN("Int / CRational")
	{
		THEN("Ok")
		{
			CRational r1(2, 5);
			CRational res1 = 2 / r1;
			CHECK(res1.GetNumerator() == 5);
			CHECK(res1.GetDenominator() == 1);
		}
	}
	WHEN("CRational / Int")
	{
		THEN("Ok")
		{
			CRational r1(2, 5);
			CRational res1 = r1 / 2;
			CHECK(res1.GetNumerator() == 1);
			CHECK(res1.GetDenominator() == 5);
		}
	}
	WHEN("CRational /= CRational")
	{
		THEN("Ok")
		{
			CRational r3(1, 2);
			CRational r4(1, 6);
			CRational res2 = r3 /= r4;
			CHECK(res2.GetNumerator() == 3);
			CHECK(res2.GetDenominator() == 1);
		}
	}
	WHEN("CRational /= Int")
	{
		THEN("Ok")
		{
			CRational r1(2, 5);
			CRational res1 = r1 /= 2;
			CHECK(res1.GetNumerator() == 1);
			CHECK(res1.GetDenominator() == 5);
		}
	}
}

SCENARIO("Operations ==")
{
	WHEN("CRational == CRational")
	{
		THEN("Ok")
		{
			CRational r1(1, 2);
			CRational r2(1, 2);
			CRational r3(1, 6);
			CHECK(r1 == r2);
			CHECK(!(r1 == r3));
		}
	}
	WHEN("Int == CRational")
	{
		THEN("Ok")
		{
			CRational r4(2);
			CRational r5(1, 2);
			CHECK(2 == r4);
			CHECK(!(2 == r5));
		}
	}
	WHEN("CRational == Int")
	{
		THEN("Ok")
		{
			CRational r6(2);
			CRational r7(1, 2);
			CHECK(r6 == 2);
			CHECK(!(r7 == 2));
		}
	}
}

SCENARIO("Operations <")
{
	WHEN("CRational < CRational")
	{
		THEN("Ok")
		{
			CRational r1(1, 6);
			CRational r2(1, 2);
			CHECK(r1 < r2);
			CHECK(!(r2 < r1));
		}
	}
	WHEN("Int < CRational")
	{
		THEN("Ok")
		{
			CRational r3(1, 6);
			CHECK(0 < r3);
			CHECK(!(2 < r3));
		}
	}
	WHEN("CRational < Int")
	{
		THEN("Ok")
		{
			CRational r4(1, 6);
			CHECK(r4 < 2);
			CHECK(!(r4 < 0));
		}
	}
}

SCENARIO("Operations <=")
{
	WHEN("CRational <= CRational")
	{
		THEN("Ok")
		{
			CRational r1(1, 6);
			CRational r2(1, 2);
			CRational r3(3, 6);
			CHECK(r1 <= r2);
			CHECK(!(r2 <= r1));
			CHECK(r2 <= r3);
		}
	}
	WHEN("Int <= CRational")
	{
		THEN("Ok")
		{
			CRational r4(6, 6);
			CHECK(0 <= r4);
			CHECK(1 <= r4);
			CHECK(!(2 <= r4));
		}
	}
	WHEN("CRational <= Int")
	{
		THEN("Ok")
		{
			CRational r5(6, 6);
			CHECK(r5 <= 2);
			CHECK(r5 <= 1);
			CHECK(!(r5 <= 0));
		}
	}
}

SCENARIO("Operations >")
{
	WHEN("CRational > CRational")
	{
		THEN("Ok")
		{
			CRational r1(1, 2);
			CRational r2(1, 6);
			CHECK(r1 > r2);
			CHECK(!(r2 > r1));
		}
	}
	WHEN("Int < CRational")
	{
		THEN("Ok")
		{
			CRational r3(1, 6);
			CHECK(1 > r3);
			CHECK(!(0 > r3));
		}
	}
	WHEN("CRational < Int")
	{
		THEN("Ok")
		{
			CRational r4(1, 6);
			CHECK(r4 > 0);
			CHECK(!(r4 > 1));
		}
	}
}

SCENARIO("Operations >=")
{
	WHEN("CRational >= CRational")
	{
		THEN("Ok")
		{
			CRational r1(1, 2);
			CRational r2(1, 6);
			CRational r3(3, 6);
			CHECK(r1 >= r2);
			CHECK(!(r2 >= r1));
			CHECK(r1 >= r3);
		}
	}
	WHEN("Int >= CRational")
	{
		THEN("Ok")
		{
			CRational r4(6, 6);
			CHECK(2 >= r4);
			CHECK(1 >= r4);
			CHECK(!(0 >= r4));
		}
	}
	WHEN("CRational >= Int")
	{
		THEN("Ok")
		{
			CRational r5(6, 6);
			CHECK(r5 >= 0);
			CHECK(r5 >= 1);
			CHECK(!(r5 >= 2));
		}
	}
}