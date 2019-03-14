#include "KCController.hpp"
#include <conio.h>
#include <ctime>

int KC::Controller::Ctrl(const int key)
{
	return key - 96;
}

int KC::Controller::KeyF(const int key)
{
	return key + 58;
}

int KC::Controller::CtrlKeyF(const int key)
{
	return key + 93;
}

bool operator==(const int& key, const KC::Controller::InputFlag& rhs)
{
	return static_cast<int>(rhs) == key;
}

int KC::Controller::GetKey(InputFlag& flag, const int delay)
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
