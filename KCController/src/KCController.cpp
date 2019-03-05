#include "KCController.hpp"

auto KC::Controller::Ctrl(const int key) -> int
{
	return key - 96;
}

auto KC::Controller::KeyF(const int key) -> int
{
	return key + 58;
}

auto KC::Controller::CtrlKeyF(const int key) -> int
{
	return key + 93;
}

auto operator==(const int& key, const KC::Controller::InputFlag& rhs) -> bool
{
	return static_cast<int>(rhs) == key;
}

auto KC::Controller::GetKey(InputFlag& flag, const time_t delay) -> int
{
	if (delay)
	{
		const auto currentTime = time(nullptr);
		while (time(nullptr) <= currentTime + delay)
		{
		}
	}
	const auto key = _getch();
	if (key == InputFlag::FlagReturn || key == InputFlag::FlagKeyReturn)
	{
		flag = InputFlag::FlagEscape;
		return GetKey(flag, 0);
	}
	if (key == InputFlag::FlagNumpad)
	{
		flag = InputFlag::FlagNumpad;
		return GetKey(flag, 0);
	}
	if (flag == InputFlag::FlagEscape || flag == InputFlag::FlagNumpad)
	{
		switch (key)
		{
		case 'H':
			return Up;
		case 'P':
			return Down;
		case 'K':
			return Left;
		case 'M':
			return Right;
		case 'G':
			return Home;
		case 'I':
			return Prior;
		case 'O':
			return End;
		case 'Q':
			return Next;
		case 'R':
			return Insert;
		case 'S':
			return Delete;
		default:
			return key;
		}
	}
	flag = InputFlag::FlagReturn;
	return key;
}
