#include "KCConsole.hpp"

KC::Console::Line::Line(SMALL_RECT const& coords, uint32_t const pattern, wchar_t const character) : SMALL_RECT{ coords }, Pattern{ pattern }, Character{ character }
{
}

KC::Console::Line::Line(COORD const& topLeft, COORD const& bottomRight, uint32_t const pattern, wchar_t const character) 
	: SMALL_RECT{ topLeft.X, topLeft.Y, bottomRight.X, bottomRight.Y }, Pattern{ pattern }, Character{ character }
{
}

KC::Console::Line::Line(short const x1, short const y1, short const x2, short const y2, uint32_t const pattern,
	wchar_t const character) : SMALL_RECT{ x1, y1, x2, y2 }, Pattern{ pattern }, Character{ character }
{
}
template <>
void KC::Console::ConsoleOutput::Write<std::wstring>(std::wstring const& in)
{
	RelativeCoord oldCursorPosition = CursorPosition;
	auto alreadyNextLine = false;
	for (auto i : in)
	{
		RelativeCoord const c = {
			Clamp(CursorPosition.X, short{0}, BufferSize.X), Clamp(CursorPosition.Y, short{0}, BufferSize.Y)
		};
		if (c.X == BufferSize.X && c.Y == BufferSize.Y)
		{
			if ((Attributes & WORD_WRAP) != WORD_WRAP) break;
			SetCursorPosition(oldCursorPosition.X, CursorPosition.Y++);
			alreadyNextLine = true;
		}
		if (i == '\n' && !alreadyNextLine)
		{
			SetCursorPosition(oldCursorPosition.X, CursorPosition.Y++);
			continue;
		}

		Buffer[CursorPosition.X + BufferSize.X * CursorPosition.Y].Attributes = ColorAttributes;
		Buffer[CursorPosition.X + BufferSize.X * CursorPosition.Y].Char.UnicodeChar = i;
		CursorPosition.X++;
	}
}
void KC::Console::ConsoleOutput::Write(const wchar_t* in)
{
	Write(std::wstring{ in });
}

void KC::Console::ConsoleOutput::Write(wchar_t const& in)
{
	Write(std::wstring{ in });
}

template <>
void KC::Console::ConsoleOutput::Write<int>(int const& in)
{
	Write(std::to_wstring(in));
}

template <>
void KC::Console::ConsoleOutput::Write<KC::Console::RelativeCoord>(RelativeCoord const& in)
{
	SetCursorPosition(in);
}

template <>
void KC::Console::ConsoleOutput::Write<KC::Console::Draw>(KC::Console::Draw const& in)
{
	Draw(in);
}

template <>
void KC::Console::ConsoleOutput::Write<KC::Colors>(Colors const& in)
{
	SetColor(in);
}

template <>
void KC::Console::ConsoleOutput::Write<KC::Console::RelativeSmallRect>(RelativeSmallRect const& in)
{
	Fill(in, L' '); // TODO: Substitute L'\0' for the full block ascii character
}

template <>
void KC::Console::ConsoleOutput::Write<KC::Console::Line>(Line const& in)
{
	DrawLine(in);
}
