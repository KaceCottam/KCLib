#include "KCStateMachine.hpp"

KC::StateMachine::StateIdentifier KC::StateMachine::GetEndString()
{
			return "end";
		}

void KC::StateMachine::RegisterState(StateIdentifier const& id, State const& func)
{
			StateFunctions[id] = func;
		}

void KC::StateMachine::RegisterTransition(StateIdentifier const& from, StateIdentifier const& to,
	Transition const& func)
{
			StateTransitions[{from, to}].push_back(func);
		}

void KC::StateMachine::RegisterTransition(TransitionIdentifier const& id, Transition const& func)
{
			TransitionFunctions[id] = func;
		}

void KC::StateMachine::BindTransition(StateIdentifier const& from, StateIdentifier const& to,
	TransitionIdentifier const& transition)
{
			StateTransitions[{from, to}].push_back(TransitionFunctions[transition]);
		}

KC::StateMachine::StateMachine(StateIdentifier const& initialState): NextState(std::move(initialState))
{
		}

KC::StateMachine::~StateMachine() = default;

void KC::StateMachine::AsyncStep()
{
}

void KC::StateMachine::Start()
{
}

KC::StateMachine::StateIdentifier KC::StateMachine::DoSingleRun(StateIdentifier const& step)
{
}

void KC::StateMachine::AsyncStep()
{
	if (NextState != "end")
	{
		auto from = NextState;
		try
		{
			NextState = StateFunctions[from]();
		}
		catch (std::exception&)
		{
			NextState = from;
		}
		try
		{
			for (auto const& i : StateTransitions.at({from, NextState}))
			{
				i();
			}
		}
		catch (std::out_of_range&)
		{
		}
	}
}
