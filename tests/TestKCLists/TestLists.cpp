#include <Test.h>
#include <KCLists/src/KCLists.hpp>

TEMPLATE_TEST_CASE("template works with multiple types","[list][multiple values][append][push]",int,double,float, char)
{
	KC::LinkedList<TestType, true> testList;
	SECTION("list is empty")
	{
		REQUIRE(testList.IsEmpty() == true);
	}

	SECTION("6 values are added to the list by Append initializer_list")
	{
		testList.Append({1, 2, 3, 4, 5, 6});
		SECTION("the list is not empty")
		{
			REQUIRE(testList.IsEmpty() == false);
		}
		SECTION("the list has a length of 6")
		{
			REQUIRE(testList.GetLength() == 6);
		}
		SECTION("traversal Node from Header is correct")
		{
			auto traversalNode = testList.GetHeader();
			TestType arrayValues[] = {1, 2, 3, 4, 5, 6};
			for (auto const& i : arrayValues)
			{
				REQUIRE(traversalNode++->Data == i);
			}
		}
		SECTION("list is verified by for loop")
		{
			for (auto i = 1; i < 7; i++)
			{
				REQUIRE(testList[i-1] == i);
			}
		}
		SECTION("list throws error when accessing bad index")
		{
			REQUIRE_THROWS([&]
			{
				testList[1000] = 0;
			}());
			REQUIRE_THROWS([&]
			{
				testList[-1] = 0;
			}());
		}
	}
	SECTION("6 values are added to the list by repeated Append")
	{
		testList.Append(1)
		        .Append(2)
		        .Append(3)
		        .Append(4)
		        .Append(5)
		        .Append(6);
		SECTION("the list is not empty")
		{
			REQUIRE(testList.IsEmpty() == false);
		}
		SECTION("the list has a length of 6")
		{
			REQUIRE(testList.GetLength() == 6);
		}
		SECTION("traversal Node from Header is correct")
		{
			auto traversalNode = testList.GetHeader();
			TestType arrayValues[] = {1, 2, 3, 4, 5, 6};
			for (auto const& i : arrayValues)
			{
				REQUIRE(traversalNode++->Data == i);
			}
		}
		SECTION("list is verified by for loop")
		{
			for (auto i = 1; i < 7; i++)
			{
				REQUIRE(testList[i-1] == i);
			}
		}
		SECTION("list throws error when accessing bad index")
		{
			REQUIRE_THROWS([&]
			{
				testList[1000] = 0;
			}());
			REQUIRE_THROWS([&]
			{
				testList[-1] = 0;
			}());
		}
	}
	SECTION("6 values are added to the list by Push initializer_list")
	{
		testList.Push({1, 2, 3, 4, 5, 6});
		SECTION("the list is not empty")
		{
			REQUIRE(testList.IsEmpty() == false);
		}
		SECTION("the list has a length of 6")
		{
			REQUIRE(testList.GetLength() == 6);
		}
		SECTION("traversal Node from Header is correct")
		{
			auto traversalNode = testList.GetHeader();
			TestType arrayValues[] = {6, 5, 4, 3, 2, 1};
			for (auto const& i : arrayValues)
			{
				REQUIRE(traversalNode++->Data == i);
			}
		}
		SECTION("list throws error when accessing bad index")
		{
			REQUIRE_THROWS([&]
			{
				testList[1000] = 0;
			}());
			REQUIRE_THROWS([&]
			{
				testList[-1] = 0;
			}());
		}
	}
	SECTION("6 values are added to the list by repeated Push")
	{
		testList.Push(1)
		        .Push(2)
		        .Push(3)
		        .Push(4)
		        .Push(5)
		        .Push(6);
		SECTION("the list is not empty")
		{
			REQUIRE(testList.IsEmpty() == false);
		}
		SECTION("the list has a length of 6")
		{
			REQUIRE(testList.GetLength() == 6);
		}
		SECTION("traversal Node from Header is correct")
		{
			auto traversalNode = testList.GetHeader();
			TestType arrayValues[] = {6, 5, 4, 3, 2, 1};
			for (auto const& i : arrayValues)
			{
				REQUIRE(traversalNode++->Data == i);
			}
		}
		SECTION("list throws error when accessing bad index")
		{
			REQUIRE_THROWS([&]
			{
				testList[1000] = 0;
			}());
			REQUIRE_THROWS([&]
			{
				testList[-1] = 0;
			}());
		}
	}
}
