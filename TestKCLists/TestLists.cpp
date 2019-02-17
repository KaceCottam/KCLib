#include "Test.h"
#include "../KCLists/src/KCLists.hpp"

SCENARIO( "KC::List<int> can be expanded", "[List][int][List<int>]")
{
	GIVEN( "A list that is initialized with nothing ")
	{
		KC::List<int> list;

		REQUIRE(list.GetLength() == 0);
		REQUIRE(*list.GetHeader() == nullptr);

		KC::TraversalNode<int> currentHeader;

		WHEN( "one thing is added" )
		{
			list.Push(1);

			THEN( "the size and header changes")
			{
				currentHeader = list.GetHeader();

				REQUIRE(list.GetLength() == 1);
				REQUIRE(*currentHeader != nullptr);
			}
		}
		WHEN("two things are added by array")
		{
			int arr[2] = { 2,3 };
			list.Push(2,arr);

			THEN("the size and header changes")
			{
				REQUIRE(list.GetLength() == 3);
				REQUIRE(*list.GetHeader() != *currentHeader);
			}
			AND_THEN("the header points to the old header when increased by two")
			{
				REQUIRE(*(list.GetHeader() += 2) == *currentHeader);
			}
		}
	}
}