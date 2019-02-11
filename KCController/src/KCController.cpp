#include "KCController.h"

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

auto KC::Controller::ToUpper(const char key) -> char
{
	if (key > 'a' && key < 'z')
	{
		return key + ('A' - 'a');
	}
	return key;
}

auto KC::Controller::ToUpper(char* string) -> char*
{
	for (auto i = 0; string[i] != '\0'; i++)
	{
		ToUpper(string[i]);
	}
	return string;
}

auto KC::Controller::ToLower(const char key) -> char
{
	if (key > 'A' && key < 'Z')
	{
		return key + ('a' - 'A');
	}
	return key;
}

auto KC::Controller::ToLower(char* string) -> char*
{
	for (auto i = 0; string[i] != '\0'; i++)
	{
		ToLower(string[i]);
	}
	return string;
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
			return KeyUpArrow;
		case 'P':
			return KeyDownArrow;
		case 'K':
			return KeyLeftArrow;
		case 'M':
			return KeyRightArrow;
		case 'G':
			return KeyHome;
		case 'I':
			return KeyPgUp;
		case 'O':
			return KeyEnd;
		case 'Q':
			return KeyPgDown;
		case 'R':
			return KeyIns;
		case 'S':
			return KeyDel;
		default:
			return key;
		}
	}
	flag = InputFlag::FlagReturn;
	return key;
}
