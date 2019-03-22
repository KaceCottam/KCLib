#include "KCConsole.hpp"

KC::Console::ColorRGB::ColorRGB(WORD const r, WORD const g, WORD const b): Value(RGB(r,g,b))
{
}

void KC::Console::ConsoleEngine::GameThread()
{
	if (!OnUserCreate())
		AtomActive = false;
	auto tp1 = std::chrono::system_clock::now();
	auto tp2 = std::chrono::system_clock::now();

	while (AtomActive)
	{
		while (AtomActive)
		{
			tp2 = std::chrono::system_clock::now();
			std::chrono::duration<float> deltaTime = tp2 - tp1;
			tp1 = tp2;
			auto dTime = deltaTime.count();
			for (auto& i : KeyLookup)
			{
				auto const keyCharacter = i.second;
				Keys[KeyIdentifierLookup[i.first]].Held = GetAsyncKeyState(keyCharacter);
				// TODO: Add Pressed and Released
			}
			if (!OnUserUpdate(dTime))
				AtomActive = false;

			wchar_t s[256];
			swprintf_s(s, 256, L"%s - FPS: %3.2f", AppName.c_str(), 1.0f / dTime);
			SetConsoleTitleW((LPCWSTR)s);
			WriteConsoleOutputW(GetStdHandle(STD_OUTPUT_HANDLE), BufferText, ScreenSize, {0, 0},
			                   &RectWindow);
		}
		if (OnUserDestroy())
		{
			// User has permitted destroy, so exit and clean up
			delete[] BufferText;
			SetConsoleActiveScreenBuffer(OriginalConsole);
			GameFinished.notify_one();
		}
		else
		{
			// User denied destroy for some reason, so continue running
			AtomActive = true;
		}
	}
}

KC::Console::ConsoleEngine::ConsoleEngine()
{
	ScreenSize.X = 80;
	ScreenSize.Y = 30;

	Console = GetStdHandle(STD_OUTPUT_HANDLE);
	ConsoleIn = GetStdHandle(STD_INPUT_HANDLE);

	AppName = L"Default";

	RegisterColor("black", 0, ColorRGB(12, 12, 12));
	RegisterColor("blue", 1, ColorRGB(0, 55, 218));
	RegisterColor("green", 2, ColorRGB(19, 161, 14));
	RegisterColor("cyan", 3, ColorRGB(58, 150, 221));
	RegisterColor("red", 4, ColorRGB(197, 15, 31));
	RegisterColor("magenta", 5, ColorRGB(136, 23, 152));
	RegisterColor("yellow", 6, ColorRGB(193, 156, 0));
	RegisterColor("white", 7, ColorRGB(204, 204, 204));
	RegisterColor("brightblack", 8, ColorRGB(118, 118, 118));
	RegisterColor("brightblue", 9, ColorRGB(59, 120, 255));
	RegisterColor("brightgreen", 10, ColorRGB(22, 198, 12));
	RegisterColor("brightcyan", 11, ColorRGB(97, 214, 214));
	RegisterColor("brightred", 12, ColorRGB(231, 72, 86));
	RegisterColor("brightmagenta", 13, ColorRGB(180, 0, 158));
	RegisterColor("brightyellow", 14, ColorRGB(249, 241, 165));
	RegisterColor("brightwhite", 15, ColorRGB(242, 242, 242));
}

KC::Console::ConsoleEngine::~ConsoleEngine()
{
	SetConsoleActiveScreenBuffer(OriginalConsole);
}

void KC::Console::ConsoleEngine::RegisterColor(std::string const& identifier, BYTE const colorTablePosition,
                                               int const r, int const b, int const g)
{
	CONSOLE_SCREEN_BUFFER_INFOEX csbi = {sizeof(CONSOLE_SCREEN_BUFFER_INFOEX)};
	GetConsoleScreenBufferInfoEx(Console, &csbi);
	csbi.ColorTable[colorTablePosition] = RGB(r,b,g);
	SetConsoleScreenBufferInfoEx(Console, &csbi);
	ColorLookup[identifier] = colorTablePosition;
}

void KC::Console::ConsoleEngine::RegisterColor(std::string const& identifier, BYTE const colorTablePosition,
                                               ColorRGB const& color)
{
	CONSOLE_SCREEN_BUFFER_INFOEX csbi = {sizeof(CONSOLE_SCREEN_BUFFER_INFOEX)};
	GetConsoleScreenBufferInfoEx(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	csbi.ColorTable[colorTablePosition] = color.Value;
	SetConsoleScreenBufferInfoEx(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	ColorLookup[identifier] = colorTablePosition;
}

void KC::Console::ConsoleEngine::ChangeColor(std::string const& identifier, ColorRGB const& color)
{
	CONSOLE_SCREEN_BUFFER_INFOEX csbi = {sizeof(CONSOLE_SCREEN_BUFFER_INFOEX)};
	GetConsoleScreenBufferInfoEx(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	csbi.ColorTable[ColorLookup[identifier]] = color.Value;
	SetConsoleScreenBufferInfoEx(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
}

void KC::Console::ConsoleEngine::ChangeColor(std::string const& identifier, int const r, int const b, int const g)
{
	CONSOLE_SCREEN_BUFFER_INFOEX csbi = {sizeof(CONSOLE_SCREEN_BUFFER_INFOEX)};
	GetConsoleScreenBufferInfoEx(Console, &csbi);
	csbi.ColorTable[ColorLookup[identifier]] = RGB(r, g, b);
	SetConsoleScreenBufferInfoEx(Console, &csbi);
}

void KC::Console::ConsoleEngine::RegisterColorAlias(std::string const& oldIdentifier, std::string const& newIdentifier)
{
	ColorLookup[newIdentifier] = ColorLookup[oldIdentifier];
}

void KC::Console::ConsoleEngine::RegisterPixelAlias(std::string const& identifier, std::string const& foregroundColor,
                                                    wchar_t const c)
{
	PixelAliasLookup[identifier] = {ColorLookup[foregroundColor], c};
}

void KC::Console::ConsoleEngine::RegisterKeyHandler(std::string const& identifier, WORD const character)
{
	KeyIdentifierLookup[identifier] = (int)KeyLookup.size();
	KeyLookup[identifier] = character;
}

KC::Console::ConsoleEngine::KeyState KC::Console::ConsoleEngine::GetKeyState(std::string const& identifier)
{
	return Keys[KeyIdentifierLookup[identifier]];
}

void KC::Console::ConsoleEngine::Draw(int const x, int const y, std::string const& pixelIdentifier)
{
	if (x >= 0 && x < ScreenSize.X && y >= 0 && y < ScreenSize.Y)
	{
		auto pix = PixelAliasLookup[pixelIdentifier];
		BufferText[y * ScreenSize.X + x].Char.UnicodeChar = pix.Character;
		BufferText[y * ScreenSize.X + x].Attributes = pix.Attributes;
		LastWritePosition.X = x;
		LastWritePosition.Y = y;
	}
}

void KC::Console::ConsoleEngine::Draw(int const x, int const y, wchar_t c, std::string const& foregroundColor)
{
	if (x >= 0 && x < ScreenSize.X && y >= 0 && y < ScreenSize.Y)
	{
		BufferText[y * ScreenSize.X + x].Char.UnicodeChar = c;
		BufferText[y * ScreenSize.X + x].Attributes = ColorLookup[foregroundColor];
		LastWritePosition.X = x;
		LastWritePosition.Y = y;
	}
}

void KC::Console::ConsoleEngine::DrawLine(int const left, int const top, int const right, int const bottom, wchar_t c,
                                          std::string const& foregroundColor, float const weight)
{
	if (left - right == 0)
	{
		auto const m = (left - right) / (float)(top - bottom);
		for (auto y = top; y <= bottom; y++)
		{
			for (auto weightOffset = - weight / 2; weightOffset <= weight / 2; weightOffset++)
			{
				Draw((int)(y * m + left + weightOffset), y, c, foregroundColor);
			}
		}
	}
	else
	{
		auto const m = (top - bottom) / (float)(left - right);
		for (auto x = left; x <= right; x++)
		{
			for (auto weightOffset = - weight / 2; weightOffset <= weight / 2; weightOffset++)
			{
				Draw(x, (int)(x * m + top + weightOffset), c, foregroundColor);
			}
		}
	}
}

void KC::Console::ConsoleEngine::DrawLine(int const left, int const top, int const right, int const bottom,
                                          std::string const& pixelIdentifier, float const weight)
{
	if (left - right == 0)
	{
		auto const m = (left - right) / (float)(top - bottom);
		for (auto y = top; y <= bottom; y++)
		{
			for (auto weightOffset = - weight / 2; weightOffset <= weight / 2; weightOffset++)
			{
				Draw((int)(y * m + left + weightOffset), y, pixelIdentifier);
			}
		}
	}
	else
	{
		auto const m = (top - bottom) / (float)(left - right);
		for (auto x = left; x <= right; x++)
		{
			for (auto weightOffset = - weight / 2; weightOffset <= weight / 2; weightOffset++)
			{
				Draw(x, (int)(x * m + top + weightOffset), pixelIdentifier);
			}
		}
	}
}

void KC::Console::ConsoleEngine::Clip(int& x, int& y) const
{
	if (x < 0) x = 0;
	if (x >= ScreenSize.X) x = ScreenSize.X;
	if (y < 0) y = 0;
	if (y >= ScreenSize.Y) y = ScreenSize.Y;
}

void KC::Console::ConsoleEngine::Fill(int left, int top, int right, int bottom, std::string const& pixelIdentifier)
{
	Clip(left, top);
	Clip(right, bottom);
	for (int x = left; x <= right; x++)
		for (int y = top; y <= bottom; y++)
			Draw(x, y, pixelIdentifier);
}

void KC::Console::ConsoleEngine::Fill(int left, int top, int right, int bottom, wchar_t c,
                                      std::string const& foregroundColor)
{
	Clip(left, top);
	Clip(right, bottom);
	for (int x = left; x <= right; x++)
		for (int y = top; y <= bottom; y++)
			Draw(x, y, c, foregroundColor);
}

void KC::Console::ConsoleEngine::DrawRect(int const left, int const top, int const right, int const bottom, wchar_t c,
                                          std::string const& foregroundColor, float const weight)
{
	DrawLine(left, top, left, bottom, c, foregroundColor, weight);
	DrawLine(right, top, right, bottom, c, foregroundColor, weight);
	DrawLine(left, top, right, top, c, foregroundColor, weight);
	DrawLine(left, bottom, right, bottom, c, foregroundColor, weight);
}

void KC::Console::ConsoleEngine::DrawRect(int const left, int const top, int const right, int const bottom,
                                          std::string const& pixelIdentifier, float const weight)
{
	DrawLine(left, top, left, bottom, pixelIdentifier, weight);
	DrawLine(right, top, right, bottom, pixelIdentifier, weight);
	DrawLine(left, top, right, top, pixelIdentifier, weight);
	DrawLine(left, bottom, right, bottom, pixelIdentifier, weight);
}

void KC::Console::ConsoleEngine::DrawString(int const x, int const y, std::wstring const& s,
                                            std::string const& foregroundColor)
{
	for ( unsigned int i = 0; i < s.size(); i++)
	{
		Draw(x + i, y, s[i], foregroundColor);
	}
}

void KC::Console::ConsoleEngine::DrawString(std::wstring const& s, std::string const& foregroundColor)
{
	DrawString(LastWritePosition.X+1,LastWritePosition.Y,s,foregroundColor);
}

void KC::Console::ConsoleEngine::DrawStringAlpha(int const x, int const y, std::wstring const& s,
                                                 std::string const& foregroundColor)
{
	for (unsigned int i = 0; i < s.size(); i++)
	{
		if (s[i] != L' ' && s[i] != L'\0')
			Draw(x + i, y, s[i], foregroundColor);
	}
}

int KC::Console::ConsoleEngine::ConstructConsole(COORD const& bufSize, COORD const& fontSize)
{
	if (Console == INVALID_HANDLE_VALUE)
		throw L"Bad Handle";

	ScreenSize = bufSize;

	Keys = new KeyState[KeyLookup.size()];

	// Update 13/09/2017 - It seems that the console behaves differently on some systems
	// and I'm unsure why this is. It could be to do with windows default settings, or
	// screen resolutions, or system languages. Unfortunately, MSDN does not offer much
	// by way of useful information, and so the resulting sequence is the reult of experiment
	// that seems to work in multiple cases.
	//
	// The problem seems to be that the SetConsoleXXX functions are somewhat circular and 
	// fail depending on the state of the current console properties, i.e. you can't set
	// the buffer size until you set the screen size, but you can't change the screen size
	// until the buffer size is correct. This coupled with a precise ordering of calls
	// makes this procedure seem a little mystical :-P. Thanks to wowLinh for helping - Jx9

	// Change console visual size to a minimum so ScreenBuffer can shrink
	// below the actual visual size
	RectWindow = {0, 0, 1, 1};
	SetConsoleWindowInfo(Console, TRUE, &RectWindow);

	// Set the size of the screen buffer
	if (!SetConsoleScreenBufferSize(Console, ScreenSize))
		throw (L"SetConsoleScreenBufferSize");

	// Assign screen buffer to the console
	if (!SetConsoleActiveScreenBuffer(Console))
		throw (L"SetConsoleActiveScreenBuffer");

	// Set the font size now that the screen buffer has been assigned to the console
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize = fontSize;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;

	wcscpy_s(cfi.FaceName, L"Courier New");
	//wcscpy_s(cfi.FaceName, L"Terminal");
	if (!SetCurrentConsoleFontEx(Console, false, &cfi))
		throw (L"SetCurrentConsoleFontEx");

	// Get screen buffer info and check the maximum allowed window size. Return
	// error if exceeded, so user knows their dimensions/fontsize are too large
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(Console, &csbi))
		throw (L"GetConsoleScreenBufferInfo");
	if (ScreenSize.Y > csbi.dwMaximumWindowSize.Y)
		throw L"Screen Height / Font Height Too Big";
	if (ScreenSize.X > csbi.dwMaximumWindowSize.X)
		throw L"Screen Width / Font Width Too Big";

	// Set Physical Console Window Size
	RectWindow = {0, 0, ScreenSize.X - 1, ScreenSize.Y - 1};
	if (!SetConsoleWindowInfo(Console, TRUE, &RectWindow))
		throw (L"SetConsoleWindowInfo");

	// Set flags to allow mouse input		
	if (!SetConsoleMode(ConsoleIn, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT))
		throw (L"SetConsoleMode");

	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = 0;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(Console, &lpCursor);

	// Allocate memory for screen buffer
	BufferText = new CHAR_INFO[ScreenSize.X * ScreenSize.Y];
	memset(BufferText, 0, sizeof(CHAR_INFO) * ScreenSize.X * ScreenSize.Y);

	return 1;
}

int KC::Console::ConsoleEngine::ConstructConsole()
{
	throw std::exception("Not implemented");
	if (Console == INVALID_HANDLE_VALUE)
		throw L"Bad Handle";

	ScreenSize = {120, 20};

	Keys = new KeyState[KeyLookup.size()];

	// Update 13/09/2017 - It seems that the console behaves differently on some systems
	// and I'm unsure why this is. It could be to do with windows default settings, or
	// screen resolutions, or system languages. Unfortunately, MSDN does not offer much
	// by way of useful information, and so the resulting sequence is the reult of experiment
	// that seems to work in multiple cases.
	//
	// The problem seems to be that the SetConsoleXXX functions are somewhat circular and 
	// fail depending on the state of the current console properties, i.e. you can't set
	// the buffer size until you set the screen size, but you can't change the screen size
	// until the buffer size is correct. This coupled with a precise ordering of calls
	// makes this procedure seem a little mystical :-P. Thanks to wowLinh for helping - Jx9

	// Change console visual size to a minimum so ScreenBuffer can shrink
	// below the actual visual size
	RectWindow = {0, 0, 1, 1};
	SetConsoleWindowInfo(Console, TRUE, &RectWindow);

	// Set the size of the screen buffer
	if (!SetConsoleScreenBufferSize(Console, ScreenSize))
		throw (L"SetConsoleScreenBufferSize");

	// Assign screen buffer to the console
	if (!SetConsoleActiveScreenBuffer(Console))
		throw (L"SetConsoleActiveScreenBuffer");

	// Set the font size now that the screen buffer has been assigned to the console
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize = {8,8};
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;

	wcscpy_s(cfi.FaceName, L"Courier New");
	wcscpy_s(cfi.FaceName, L"Terminal");
	if (!SetCurrentConsoleFontEx(Console, false, &cfi))
		throw (L"SetCurrentConsoleFontEx");


	// Set Physical Console Window Size
	RectWindow = {0, 0, ScreenSize.X - 1, ScreenSize.Y - 1};
	//if (!SetConsoleWindowInfo(Console, TRUE, &RectWindow))
	//throw (L"SetConsoleWindowInfo");

	// Set flags to allow mouse input		
	if (!SetConsoleMode(ConsoleIn, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT))
		throw (L"SetConsoleMode");

	// Allocate memory for screen buffer
	BufferText = new CHAR_INFO[ScreenSize.X * ScreenSize.Y];
	memset(BufferText, 0, sizeof(CHAR_INFO) * ScreenSize.X * ScreenSize.Y);

	return 1;
}

void KC::Console::ConsoleEngine::Start()
{
	// Start the thread
	AtomActive = true;
	std::thread t = std::thread(&ConsoleEngine::GameThread, this);

	// Wait for thread to be exited
	t.join();
}

std::atomic<bool> KC::Console::ConsoleEngine::AtomActive(false);
std::condition_variable KC::Console::ConsoleEngine::GameFinished;
std::mutex KC::Console::ConsoleEngine::GameThreadMutex;
