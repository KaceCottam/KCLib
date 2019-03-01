#pragma once

#include <map>
#include <string>
#include <functional>

using std::map;
using std::string;
using std::function;
using std::initializer_list;
using std::pair;

using FunctionInitializerList = initializer_list<pair<int, function<void()>>>;

namespace KC
{
	class StateMachine
	{
		struct StateMachineEvent {};

		map<int, function<void()>> StateFunctions;

		int CurrentState = 0;

		int const MaxStates = 0;
	protected:
		void RegisterState(int const id, function<void()> const& func)
		{
			StateFunctions[id] = func;
		}

		void RegisterStates(FunctionInitializerList const& funcList)
		{
			for (auto const& i : funcList)
			{
				RegisterState(i.first, i.second);
			}
		}

		enum StateStatus
		{
			Failed = -1,
			Initial = 0,
		};

		void SetInitialState()
		{
			CurrentState = 0;
		}

		StateMachine(int const maxStates, FunctionInitializerList const& funcList = {}) : MaxStates(maxStates)
		{
			RegisterStates(funcList);
		}


	};
}


