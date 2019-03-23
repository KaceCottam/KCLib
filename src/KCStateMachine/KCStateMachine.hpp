//@KCLIB_FILE_COMMENT@
#pragma once
#include <unordered_map>
#include <string>
#include <functional>
#include <utility>
#include <vector>

namespace std
{
	template <> struct hash<pair<std::string, std::string>>
	{
		size_t operator()(const pair<std::string, std::string>& x) const
		{
			return size_t(39 * x.first[0] | x.second[0]);
		}
	};
}

namespace KC
{
	using std::unordered_map;
	using std::string;
	using std::function;
	using std::initializer_list;
	using std::pair;
	using std::vector;

	class StateMachine
	{
	protected:
		using StateIdentifier = string;
		using State = function<StateIdentifier()>;
		using TransitionIdentifier = string;
		using Transition = function<void()>;
		unordered_map<StateIdentifier, State> StateFunctions;
		unordered_map<TransitionIdentifier, Transition> TransitionFunctions;
		unordered_map<pair<StateIdentifier, StateIdentifier>, vector<Transition>> StateTransitions;

		virtual StateIdentifier GetEndString()
		{
			return "end";
		}

		StateIdentifier NextState;

		void RegisterState(StateIdentifier const& id, State const& func)
		{
			StateFunctions[id] = func;
		}

		void RegisterTransition(StateIdentifier const& from, StateIdentifier const& to,
			Transition const& func)
		{
			StateTransitions[{from, to}].push_back(func);
		}

		void RegisterTransition(TransitionIdentifier const& id, Transition const& func)
		{
			TransitionFunctions[id] = func;
		}

		void BindTransition(StateIdentifier const& from, StateIdentifier const& to,
			TransitionIdentifier const& transition)
		{
			StateTransitions[{from, to}].push_back(TransitionFunctions[transition]);
		}

		explicit StateMachine(StateIdentifier const& initialState) : NextState(std::move(initialState))
		{
		}

	public:
		virtual ~StateMachine() ;

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
					for (auto const& i : StateTransitions.at({ from,NextState }))
					{
						i();
					}
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

		StateIdentifier DoSingleRun(StateIdentifier const& step)
		{
			return StateFunctions[step]();
		}
	};
}
