#include <Test.h>
#include <KCStateMachine/src/KCStateMachine.hpp>

SCENARIO("A basic state machine with one data type")
{
	GIVEN("A state machine with a single state and data")
	{
		class MainState : public KC::StateMachine
		{
		public:
			int increments = 0;

			MainState() : StateMachine("increment")
			{
				RegisterState("increment", [&]()
				{
					this->increments++;
					if (this->increments < 8)
					{
						return "increment";
					}
					return "end";
				});
			}

			REGISTER_VARIABLES;
		} mainState;

		WHEN("the state machine is not started")
		{
			THEN("there are 0 increments")
			{
				REQUIRE(mainState.increments == 0);
			}
		}
		AND_WHEN("the state machine is started")
		{
			mainState.Start();
			THEN("there are 8 increments")
			{
				REQUIRE(mainState.increments == 8);
			}
		}
	}
	AND_GIVEN("a state machine with two states and a transition between them")
	{
		class MainState : public KC::StateMachine
		{
		public:
			int increment = 0;
			MainState() : StateMachine("a")
			{
				RegisterState("a",[this]()
				{
				increment++;
					return "b";
				});
				RegisterState("b",[this]()
				{
					increment++;
					if(increment==7)
					{
						return "end";
					}
					return "a";
				});
				RegisterTransition("a","b",[this]()
				{
					increment++;
				});
				RegisterTransition("b","a",[this]()
				{
					increment++;
				});
				RegisterTransition("b","end",[this]()
				{
					increment++;
				});
			}

			REGISTER_VARIABLES;
		} mainState;

		WHEN("started")
		{
			mainState.Start();
			THEN("increment is 8")
			{
				REQUIRE(mainState.increment == 8);
			}
		}
	}
}
