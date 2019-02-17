#pragma once
#include <Test.h>
#include <KCLists.hpp>

SCENARIO("KC::List<int> can be expanded", "[List][int][List<int>]")
{
	GIVEN("A list that is initialized with nothing ")
	{
		KC::List<int> list;
		WHEN("nothing is added to the list")
		{
			THEN("the list has nothing inside of it")
			{
				REQUIRE(list.GetLength() == 0);
			}
			AND_THEN("the list's header is pointing to nothing")
			{
				REQUIRE(*list.GetHeader() == nullptr);
			}
		}

		KC::TraversalNode<int> currentHeader;

		WHEN("one thing is added")
		{
			list.Push(1);
			currentHeader = list.GetHeader();

			THEN("the size changes")
			{
				REQUIRE(list.GetLength() == 1);
			}
			AND_THEN("the header is no longer null")
			{
				REQUIRE(*currentHeader != nullptr);
			}
			AND_WHEN("two things are added by array")
			{
				int arr[2] = { 2,3 };
				list.Push(2, arr);

				THEN("the size changes")
				{
					REQUIRE(list.GetLength() == 3);
				}
				AND_THEN("the header is not the old header")
				{
					REQUIRE(*list.GetHeader() != *currentHeader);
				}
				AND_THEN("the header points to the old header when increased by two")
				{
					REQUIRE(*(list.GetHeader() += 2) == *currentHeader);
				}

				currentHeader = list.GetHeader();

				AND_WHEN("three things are added by initializer list")
				{
					list.Push({ 4,5,6 });

					THEN("the size changes again")
					{
						REQUIRE(list.GetLength() == 6);
					}
					AND_THEN("the header is no longer the previous header")
					{
						REQUIRE(*list.GetHeader() != *currentHeader);
					}
					AND_THEN("the header points to the old header when increased by three")
					{
						REQUIRE(*(list.GetHeader() += 3) == *currentHeader);
					}

					currentHeader = list.GetHeader();

					AND_WHEN("a copy of the list is added to itself")
					{
						auto listCpy = list;
						list.Push(listCpy);

						THEN("the size doubles")
						{
							REQUIRE(list.GetLength() == 12);
						}
						AND_THEN("the header is no longer the previous header")
						{
							REQUIRE(*list.GetHeader() != *currentHeader);
						}
						AND_THEN("the header points to the old header when increased by six")
						{
							REQUIRE(*(list.GetHeader() += 6) == *currentHeader);
						}
						AND_THEN("the list is correct")
						{
							REQUIRE(list[0] == 4);
							REQUIRE(list[1] == 5);
							REQUIRE(list[2] == 6);
							REQUIRE(list[3] == 2);
							REQUIRE(list[4] == 3);
							REQUIRE(list[5] == 1);
							REQUIRE(list[6] == 4);
							REQUIRE(list[7] == 5);
							REQUIRE(list[8] == 6);
							REQUIRE(list[9] == 2);
							REQUIRE(list[10] == 3);
							REQUIRE(list[11] == 1);
						}
					}
					AND_WHEN("the list is added to itself")
					{
						list.Push(list);
						THEN("the size doubles")
						{
							REQUIRE(list.GetLength() == 12);
						}
						AND_THEN("the header is no longer the previous header")
						{
							REQUIRE(*list.GetHeader() != *currentHeader);
						}
						AND_THEN("the header points to the old header when increased by six")
						{
							REQUIRE(*(list.GetHeader() += 6) == *currentHeader);
						}
						AND_THEN("the list is correct")
						{
							REQUIRE(list[0] == 5);
							REQUIRE(list[1] == 5);
							REQUIRE(list[2] == 1);
							REQUIRE(list[3] == 5);
							REQUIRE(list[4] == 2);
							REQUIRE(list[5] == 1);
							REQUIRE(list[6] == 4);
							REQUIRE(list[7] == 5);
							REQUIRE(list[8] == 6);
							REQUIRE(list[9] == 2);
							REQUIRE(list[10] == 3);
							REQUIRE(list[11] == 1);
						}
					}
				}
			}
		}
	}
	GIVEN("A list that is initialized with an array of 2 integers")
	{
		int arr[2] = { 10,9 };
		KC::List<int> list(2, arr);

		REQUIRE(list.GetLength() == 2);
		REQUIRE(*list.GetHeader() != nullptr);

		WHEN("pulled from")
		{
			auto headNode = list.GetHeader();
			auto a = list.Pull();

			THEN("the data is correctly pulled")
			{
				REQUIRE(a == 10);
			}
			AND_THEN("the list is resized acccordingly")
			{
				REQUIRE(list.GetLength() == 1);
			}
		}
	}
}