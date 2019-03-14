#pragma once

#include <map>
#include <string>
#include <functional>
#include <utility>
#include <vector>

using std::map;
using std::string;
using std::function;
using std::initializer_list;
using std::pair;
using std::vector;

using NextState = string;
using FunctionInitializerList = initializer_list<pair<string, function<NextState()>>>;
using StateIdentifier = string;
using State = function<NextState()>;
using TransitionInitializerList = initializer_list<pair<pair<StateIdentifier, StateIdentifier>, function<void()>>>;

namespace KC
{
	class StateMachine
	{
	protected:
		map<StateIdentifier, State> StateFunctions;
		map<pair<StateIdentifier, StateIdentifier>, function<void()>> StateTransitions;
		virtual StateIdentifier GetEndString()
		{
			return "end";
		}
		StateIdentifier NextState = GetEndString();

		void RegisterState(StateIdentifier const& id, State const& func)
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

		void RegisterTransition(StateIdentifier const& from, StateIdentifier const& to, function<void()> const& func)
		{
			StateTransitions[{from, to}] = func;
		}

		void RegisterTransitions(TransitionInitializerList const& funcList)
		{
			for (auto const& i : funcList)
			{
				RegisterTransition(i.first.first, i.first.second, i.second);
			}
		}

		StateMachine(StateIdentifier initialState) : NextState(std::move(initialState))
		{
		}

	public:
		void AsyncStep() 
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
					StateTransitions.at({from, NextState})(); 
				} 
				catch (std::out_of_range&) 
				{ 
				} 
			} 
		} 
		void Start() 
		{ 
			while (NextState != GetEndString()) 
			{ 
				AsyncStep(); 
			} 
		}
		virtual StateIdentifier DoSingleRun(StateIdentifier const& step)
		{
			return StateFunctions[step]();
		}
	};
}
