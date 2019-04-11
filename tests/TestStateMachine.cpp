#include <Catch2/catch.hpp>
#include <KCLib/KCStateMachine.hpp>

SCENARIO("A basic state machine with one data type", "[state machine][state]")
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
				RegisterState("a", [this]()
				{
					increment++;
					return "b";
				});
				RegisterState("b", [this]()
				{
					increment++;
					if (increment >= 7)
					{
						return "end";
					}
					return "a";
				});
				RegisterTransition("inc", [this]()
				{
					increment++;
				});
				BindTransition("b", "a", "inc");
			}
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
	AND_GIVEN("a state machine with one state and multiple transitions")
	{
		class SM : public KC::StateMachine
		{
		public:
			int increments = 0;
			SM() : StateMachine("init")
			{
				RegisterState("init",[this]
				{
					increments++;
					return "end";
				});

				RegisterTransition("init","end",[this]
				{
					increments--;
				});

				RegisterTransition("init","end",[this]
				{
					increments++;
				});
			}
		} stateMachine;
		WHEN("started")
		{
			stateMachine.Start();
			THEN("increments is 1")
			{
				REQUIRE(stateMachine.increments == 1);
			}
		}
	}
	AND_GIVEN("a state machine with one state and a different end string")
	{
		class SM : public KC::StateMachine
		{
		protected:
			StateIdentifier GetEndString() override
			{
				return "yes";
			}

		public:
			int increments = 0;
			SM() : StateMachine("yes")
			{
				RegisterState("no", [&]
				{
					increments--;
					return "yes";
				});
			}
		} stateMachine;

		WHEN("started")
		{
			stateMachine.Start();
			THEN("increment is 0")
			{
				REQUIRE(stateMachine.increments == 0);
			}
		}
		
	}
}
