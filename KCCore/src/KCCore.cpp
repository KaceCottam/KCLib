#include "KCCore.h"
#include <Windows.h>
#include <ctime>

HANDLE kcStdout;

auto KC::Core::EnableConsoleColor() -> void
{
	DWORD dwMode = 0;
	GetConsoleMode(kcStdout, &dwMode);
	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	SetConsoleMode(kcStdout, dwMode);
}

auto KC::Core::ResizeCursor(const unsigned int visible) -> void
{
	CONSOLE_CURSOR_INFO info;
	info.dwSize = visible ? visible : 10;
	info.bVisible = visible ? 1 : 0;
	SetConsoleCursorInfo(kcStdout, &info);
}

auto KC::Core::SetupKCLib() -> void
{
	kcStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	randomizationSeed = static_cast<unsigned int>(time(nullptr));
	srand(randomizationSeed);
	EnableConsoleColor();
}
