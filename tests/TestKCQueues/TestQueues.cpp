#include <Test.h>
#include <KCQueues.hpp>

TEMPLATE_TEST_CASE("test queue with multiple types","[queue][enqueue][dequeue][multiple values]",int, char, long, long long, float, double)
{
	KC::Queue<TestType> testQueue;
	SECTION("nothing is done")
	{
		REQUIRE(testQueue.IsEmpty() == true);
		REQUIRE(testQueue.GetLength() == 0);
		REQUIRE_THROWS([&]
		{
			testQueue.Dequeue();
		}());
	}
	SECTION("queue with repeated enqueue")
	{
		testQueue.Enqueue(1)
		         .Enqueue(2)
		         .Enqueue(3)
		         .Enqueue(4)
		         .Enqueue(5)
		         .Enqueue(6);
		REQUIRE(testQueue.IsEmpty() == false);
		REQUIRE(testQueue.GetLength() == 6);

		auto a = testQueue.Dequeue();
		REQUIRE(testQueue.GetLength() == 5);
		REQUIRE(a == 1);
	}
	SECTION("queue with initializer list")
	{
		testQueue.Enqueue({1, 2, 3, 4, 5, 6});
		REQUIRE(testQueue.IsEmpty() == false);
		REQUIRE(testQueue.GetLength() == 6);

		auto a = testQueue.Dequeue();
		REQUIRE(testQueue.GetLength() == 5);
		REQUIRE(a == 1);
	}
}
