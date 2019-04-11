#include <Catch2/catch.hpp>
#include <KCLib/KCStacks.hpp>

TEMPLATE_TEST_CASE("stacks work with many data types","[stack][array][data structure]",int,char,double,float,long,long long)
{
	KC::Stack<TestType> stack;
	SECTION("stack is empty at first")
	{
		REQUIRE(stack.IsEmpty());
		REQUIRE(stack.GetSize() == 0);
		REQUIRE_THROWS([&]{stack.Peek();}());
	}
	SECTION("two items are inserted into the stack")
	{
		stack.Push({5,10});
		SECTION("stack is no longer empty")
		{
			REQUIRE(!stack.IsEmpty());
			REQUIRE(stack.GetSize() == 2);
		}
		SECTION("Stack has correct data")
		{
			REQUIRE(stack.Peek() == 10);
			REQUIRE(stack.Peek(0) == 5);
		}
	}
}