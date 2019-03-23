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

		virtual StateIdentifier GetEndString();

		StateIdentifier NextState;

		void RegisterState(StateIdentifier const& id, State const& func);

		void RegisterTransition(StateIdentifier const& from, StateIdentifier const& to,
			Transition const& func); 
		void RegisterTransition(TransitionIdentifier const& id, Transition const& func);

		void BindTransition(StateIdentifier const& from, StateIdentifier const& to,
			TransitionIdentifier const& transition);

		explicit StateMachine(StateIdentifier const& initialState);

	public:
		virtual ~StateMachine();

		void AsyncStep();

		void Start();

		StateIdentifier DoSingleRun(StateIdentifier const& step);
	};
}
