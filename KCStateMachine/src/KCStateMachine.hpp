#pragma once

#include <functional>
#include <vector>
#include <utility>

namespace KC
{
	template<class... DataTypes>
	class StateMachine final
	{
		bool FlagStop = false;
		int CurrentStateIndex = 0;
		std::tuple<DataTypes> Data;
	public:
		std::vector<std::function<void(StateMachine&)>> States;
		std::function<void(StateMachine&)> NextState;

		explicit StateMachine(DataTypes& data)
			: Data(data)
		{
		}
		explicit StateMachine(std::vector<std::function<void(StateMachine&)>> states)
			: Data(nullptr), States(states), NextState(states.front())
		{
		}
		explicit StateMachine(std::initializer_list<std::function<void(StateMachine&)>> states)
			: Data(nullptr), States(std::vector<std::function<void(StateMachine&)>>(states)), NextState(states[0])
		{
		}

		void Start()
		{
			while (NextState != nullptr && !FlagStop)
			{
				NextState(*this);
			}
			FlagStop = false;
		}

		bool Stop()
		{
			const auto stopped = !this->IsStopped();
			FlagStop = true;
			return stopped;
		}

		bool IsStopped() const
		{
			return FlagStop;
		}

		StateMachine<DataTypes>& operator++()
		{
			CurrentStateIndex++;
			NextState = States[CurrentStateIndex];
			return *this;
		}

		StateMachine<DataTypes>& operator--()
		{
			CurrentStateIndex--;
			while (CurrentStateIndex < 0) CurrentStateIndex++;
			NextState = States[CurrentStateIndex];
			return *this;
		}

		explicit operator bool() const { return IsStopped(); }
	};
}
