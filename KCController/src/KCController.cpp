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
			return VK_UP;
		case 'P':
			return VK_DOWN;
		case 'K':
			return VK_LEFT;
		case 'M':
			return VK_RIGHT;
		case 'G':
			return VK_HOME;
		case 'I':
			return VK_PRIOR;
		case 'O':
			return VK_END;
		case 'Q':
			return VK_NEXT;
		case 'R':
			return VK_INSERT;
		case 'S':
			return VK_DELETE;
		default:
			return key;
		}
	}
	flag = InputFlag::FlagReturn;
	return key;
}
