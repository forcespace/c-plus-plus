#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../CMyList/CMyList.h"

TEST_CASE("check functional of constructors")
{
	GIVEN("list with size 0")
	{
		CMyList<int> list;

		THEN("size = 0")
		{
			REQUIRE(list.Size() == 0);
		}

		THEN("list is empty")
		{
			REQUIRE(list.IsEmpty());
		}
	}

	GIVEN("list with size 0")
	{
		CMyList<int> list;

		WHEN("new list = list")
		{
			CMyList<int> newList(list);

			THEN("size = 0")
			{
				REQUIRE(newList.Size() == 0);
			}

			THEN("new list is empty")
			{
				REQUIRE(list.IsEmpty());
			}
		}
	}

	GIVEN("list with size 2")
	{
		CMyList<int> list;
		list.PushFront(1);
		list.PushBack(2);

		WHEN("new list = list")
		{
			CMyList<int> newList(list);

			THEN("size = 2")
			{
				REQUIRE(newList.Size() == 2);
			}

			THEN("elements: 1, 2")
			{
				REQUIRE(newList.GetFrontElement() == 1);
				REQUIRE(newList.GetBackElement() == 2);
			}
		}
	}
}

TEST_CASE("check functional of assignment")
{
	GIVEN("list with size 2")
	{
		CMyList<int> list;
		list.PushFront(1);
		list.PushBack(2);

		WHEN("list = list")
		{
			list = list;

			THEN("size = 2")
			{
				REQUIRE(list.Size() == 2);
			}

			THEN("elements: 1, 2")
			{
				REQUIRE(list.GetFrontElement() == 1);
				REQUIRE(list.GetBackElement() == 2);
			}
		}
	}

	GIVEN("list with size 2")
	{
		CMyList<int> list;
		list.PushFront(1);
		list.PushBack(2);

		WHEN("new list = list")
		{
			CMyList<int> newList;
			newList = list;

			THEN("size = 2")
			{
				REQUIRE(newList.Size() == 2);
			}

			THEN("elements: 1, 2")
			{
				REQUIRE(newList.GetFrontElement() == 1);
				REQUIRE(newList.GetBackElement() == 2);
			}
		}
	}

	GIVEN("list = the same list with moving")
	{
		CMyList<int> list;
		list.PushFront(1);
		list.PushBack(2);

		WHEN("list = list")
		{
			list = std::move(list);

			THEN("size = 2")
			{
				REQUIRE(list.Size() == 2);
			}

			THEN("elements: 1, 2")
			{
				REQUIRE(list.GetFrontElement() == 1);
				REQUIRE(list.GetBackElement() == 2);
			}
		}
	}

	GIVEN("list with size 2 with moving")
	{
		CMyList<int> list;
		list.PushFront(1);
		list.PushBack(2);

		WHEN("new list = list")
		{
			CMyList<int> newList = std::move(list);

			THEN("size = 2")
			{
				REQUIRE(newList.Size() == 2);
			}

			THEN("elements: 1, 2")
			{
				REQUIRE(newList.GetFrontElement() == 1);
				REQUIRE(newList.GetBackElement() == 2);
			}

			THEN("old list size = 0")
			{
				REQUIRE(list.Size() == 0);
			}
		}
	}
}

TEST_CASE("check functional of delete")
{
	GIVEN("list with size 0")
	{
		CMyList<int> list;

		WHEN("delete begin()")
		{
			THEN("exception")
			{
				REQUIRE_THROWS(list.Delete(list.begin()));
				REQUIRE_THROWS_AS(list.Delete(list.begin()), UnableDeleteElementError);
			}
		}

		WHEN("delete end()")
		{
			THEN("exception")
			{
				REQUIRE_THROWS(list.Delete(list.end()));
				REQUIRE_THROWS_AS(list.Delete(list.end()), UnableDeleteElementError);
			}
		}
	}
}

TEST_CASE("check functional of iterators")
{
	GIVEN("list with size 0")
	{
		CMyList<int> list;

		WHEN("iterator end() ++")
		{
			THEN("exception")
			{
				REQUIRE_THROWS(list.end()++);
				REQUIRE_THROWS_AS(list.end()++, UnableChangeIteratorError);
			}
		}
	}

	GIVEN("list with size 2")
	{
		CMyList<int> list;
		list.PushFront(1);
		list.PushFront(2);

		WHEN("iterator begin() ++")
		{
			THEN("exception")
			{
				REQUIRE_NOTHROW(list.begin()++);
			}
		}

		WHEN("iterator end() --")
		{
			THEN("exception")
			{
				REQUIRE_NOTHROW(list.end()--);
			}
		}

		WHEN("iterator end() ++")
		{
			THEN("exception")
			{
				REQUIRE_THROWS(list.end()++);
				REQUIRE_THROWS_AS(list.end()++, UnableChangeIteratorError);
			}
		}

		WHEN("iterator rend() and rbegin()")
		{
			THEN("*rend() = 2 *rbegin() = 1")
			{
				REQUIRE(*(--list.rend()) == 2);
				REQUIRE(*list.rbegin() == 1);
			}
		}

		WHEN("iterator = rend()")
		{
			auto iterator = list.rend();

			THEN("*(--iterator) = 2")
			{
				REQUIRE_THROWS(*iterator);
				REQUIRE_THROWS_AS(*iterator, UnableGetElementError);
				REQUIRE(*(--iterator) == 2);
			}
		}
	}
}

TEST_CASE("check functional of push")
{
	GIVEN("list with size 0 type of int")
	{
		CMyList<int> list;

		WHEN("push 0 element")
		{
			THEN("size = 0")
			{
				REQUIRE(list.Size() == 0);
			}

			THEN("list is empty")
			{
				REQUIRE(list.IsEmpty());
			}
		}
		
		WHEN("push front 1 element")
		{
			list.PushFront(1);

			THEN("size = 1")
			{
				REQUIRE(list.Size() == 1);
			}

			THEN("list is not empty")
			{
				REQUIRE_FALSE(list.IsEmpty());
			}
		}

		WHEN("push front 2 element")
		{
			list.PushFront(1);
			list.PushFront(2);

			THEN("size = 2")
			{
				REQUIRE(list.Size() == 2);
			}

			THEN("list is not empty")
			{
				REQUIRE_FALSE(list.IsEmpty());
			}
		}

		WHEN("push back 1 element")
		{
			list.PushBack(1);

			THEN("size = 1")
			{
				REQUIRE(list.Size() == 1);
			}

			THEN("list is not empty")
			{
				REQUIRE_FALSE(list.IsEmpty());
			}
		}

		WHEN("push back 2 element")
		{
			list.PushBack(1);
			list.PushBack(2);

			THEN("size = 2")
			{
				REQUIRE(list.Size() == 2);
			}

			THEN("list is not empty")
			{
				REQUIRE_FALSE(list.IsEmpty());
			}
		}

		WHEN("push back with push front 2 element")
		{
			list.PushBack(1);
			list.PushFront(2);

			THEN("size = 2")
			{
				REQUIRE(list.Size() == 2);
			}

			THEN("list is not empty")
			{
				REQUIRE_FALSE(list.IsEmpty());
			}
		}

		WHEN("push front with insert front 2 element")
		{
			list.Insert(list.begin(), 1);
			list.Insert(list.begin(), 2);

			THEN("size = 2")
			{
				REQUIRE(list.Size() == 2);
			}

			THEN("list is not empty")
			{
				REQUIRE_FALSE(list.IsEmpty());
			}
		}

		WHEN("push front and after first")
		{
			list.Insert(list.begin(), 1);
			list.Insert(list.begin()++, 2);

			THEN("size = 2")
			{
				REQUIRE(list.Size() == 2);
			}

			THEN("list is not empty")
			{
				REQUIRE_FALSE(list.IsEmpty());
			}
		}
	}
}

TEST_CASE("test of getting elements")
{
	GIVEN("list with 0 elements")
	{
		CMyList<int> list;

		WHEN("get front")
		{
			THEN("exception")
			{
				REQUIRE_THROWS(list.GetFrontElement());
				REQUIRE_THROWS_AS(list.GetFrontElement(), UnableGetElementError);
			}
		}

		WHEN("get back")
		{
			THEN("exception")
			{
				REQUIRE_THROWS(list.GetBackElement());
				REQUIRE_THROWS_AS(list.GetBackElement(), UnableGetElementError);
			}
		}
	}

	GIVEN("list with 1 elements")
	{
		CMyList<int> list;
		list.PushFront(1);

		WHEN("get front")
		{
			int element = list.GetFrontElement();

			THEN("element = 1")
			{
				REQUIRE(element == 1);
				REQUIRE(list.Size() == 1);
			}
		}

		WHEN("get back")
		{
			int element = list.GetBackElement();

			THEN("element = 1")
			{
				REQUIRE(element == 1);
				REQUIRE(list.Size() == 1);
			}
		}

		WHEN("const get front")
		{
			const int element = list.GetFrontElement();

			THEN("element = 1")
			{
				REQUIRE(element == 1);

				REQUIRE(list.Size() == 1);
			}
		}

		WHEN("const get back")
		{
			const int element = list.GetBackElement();

			THEN("element = 1")
			{
				REQUIRE(element == 1);

				REQUIRE(list.Size() == 1);
			}
		}
	}

	GIVEN("list with 2 elements")
	{
		CMyList<int> list;
		list.PushFront(1);
		list.PushFront(2);

		WHEN("get front")
		{
			int element = list.GetFrontElement();

			THEN("element = 2")
			{
				REQUIRE(element == 2);
				REQUIRE(list.Size() == 2);
			}
		}

		WHEN("get back")
		{
			int element = list.GetBackElement();

			THEN("element = 1")
			{
				REQUIRE(element == 1);
				REQUIRE(list.Size() == 2);
			}
		}

		WHEN("const get front")
		{
			const int element = list.GetFrontElement();

			THEN("element = 2")
			{
				REQUIRE(element == 2);

				REQUIRE(list.Size() == 2);
			}
		}

		WHEN("const get back")
		{
			const int element = list.GetBackElement();

			THEN("element = 1")
			{
				REQUIRE(element == 1);

				REQUIRE(list.Size() == 2);
			}
		}
	}
}