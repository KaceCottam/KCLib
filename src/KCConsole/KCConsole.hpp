//@KC_FILE_COMMENT@
#pragma once
#include <Windows.h>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
#include <conio.h>

#define NOT_IMPLEMENTED 0 // Error Code

/*
 * TODO:
 * Implement KC::Console::Handler class, which manages console.
 * It can change color of fonts, change font family and size,
 * resize console, hold multiple output panes (accessed by [])
 */
inline COORD operator-(COORD const& lhs, COORD const& rhs)
{
	return { static_cast<SHORT>(lhs.X - rhs.X), static_cast<SHORT>(lhs.Y - rhs.Y) };
}

inline COORD operator+(COORD const& lhs, COORD const& rhs)
{
	return { static_cast<SHORT>(lhs.X + rhs.X), static_cast<SHORT>(lhs.Y + rhs.Y) };
}

namespace KC
{
	namespace Util
	{
		template <class T, class = typename std::is_literal_type<T>::value>
		class Attribute
		{
			// TODO: Finish
		};
	}

	enum Colors : WORD
	{
		// Foreground Colors
		F_BRIGHT = FOREGROUND_INTENSITY,
		F_RED = FOREGROUND_RED,
		F_BLUE = FOREGROUND_BLUE,
		F_GREEN = FOREGROUND_GREEN,
		F_MAGENTA = FOREGROUND_RED | FOREGROUND_BLUE,
		F_YELLOW = FOREGROUND_RED | FOREGROUND_GREEN,
		F_CYAN = FOREGROUND_BLUE | FOREGROUND_GREEN,
		F_WHITE = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN,

		// Background Colors
		B_BRIGHT = BACKGROUND_INTENSITY,
		B_RED = BACKGROUND_RED,
		B_BLUE = BACKGROUND_BLUE,
		B_GREEN = BACKGROUND_GREEN,
		B_MAGENTA = BACKGROUND_RED | BACKGROUND_BLUE,
		B_YELLOW = BACKGROUND_RED | BACKGROUND_GREEN,
		B_CYAN = BACKGROUND_BLUE | BACKGROUND_GREEN,
		B_WHITE = BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN,

		// Whole Pixel Colors
		P_BRIGHT = F_BRIGHT | B_BRIGHT,
		P_RED = F_RED | B_RED,
		P_BLUE = F_BLUE | B_BLUE,
		P_GREEN = F_GREEN | B_GREEN,
		P_MAGENTA = F_MAGENTA | B_MAGENTA,
		P_YELLOW = F_YELLOW | B_YELLOW,
		P_CYAN = F_CYAN | B_CYAN,
		P_WHITE = F_WHITE | B_WHITE,
		P_BLACK = 0U,

		P_DEFAULT = F_WHITE,
		F_DEFAULT = F_WHITE,
		B_DEFAULT = 0U
	};

	namespace Console
	{
		using RelativeSmallRect = SMALL_RECT;
		using WorldSmallRect = SMALL_RECT;
		using RelativeCoord = COORD;
		using WorldCoord = COORD;

		struct Draw
		{
			bool Reset{ false };
		};

		struct Line : SMALL_RECT
		{
			uint32_t Pattern;
			wchar_t Character;

			explicit Line(SMALL_RECT const& coords, uint32_t const pattern = 0xFFFFFFFF, wchar_t const character = L' ');

			Line(COORD const& topLeft, COORD const& bottomRight, uint32_t const pattern = 0xFFFFFFFF,
				wchar_t const character = L' ');

			Line(short const x1, short const y1, short const x2, short const y2, uint32_t const pattern = 0xFFFFFFFF,
				wchar_t const character = L' ');
		};

		class ConsoleOutput
		{
		public:
			ConsoleOutput(const ConsoleOutput& other)
				: DrawArea{ other.DrawArea }
				, ConsoleHandle{ other.ConsoleHandle }
				, BufferSize{ other.BufferSize }
				, Buffer{ new CHAR_INFO[BufferSize.X*BufferSize.Y] }
			{
				std::memcpy(Buffer, other.Buffer, sizeof(*Buffer)*BufferSize.X * BufferSize.Y);
				SetColor();
			}
			ConsoleOutput(ConsoleOutput&& other) noexcept
				: DrawArea{ other.DrawArea }
				, ConsoleHandle{ other.ConsoleHandle }
				, BufferSize{ other.BufferSize }
				, Buffer{ other.Buffer }
			{
				SetColor();
			}
			ConsoleOutput& operator=(const ConsoleOutput& other)
			{
				if (this == &other)
					return *this;
				DrawArea = other.DrawArea;
				ConsoleHandle = other.ConsoleHandle;
				BufferSize.X = other.BufferSize.X;
				BufferSize.Y = other.BufferSize.Y;
				if (Buffer != nullptr)
				{
					delete[] Buffer;
					Buffer = nullptr;
				}
				Buffer = new CHAR_INFO[BufferSize.X*BufferSize.Y];
				std::memcpy(Buffer, other.Buffer, sizeof(*Buffer)*BufferSize.X * BufferSize.Y);
				SetColor();
				return *this;
			}
			ConsoleOutput& operator=(ConsoleOutput&& other) noexcept
			{
				if (this == &other)
					return *this;
				DrawArea = other.DrawArea;
				ConsoleHandle = other.ConsoleHandle;
				BufferSize.X = other.BufferSize.X;
				BufferSize.Y = other.BufferSize.Y;
				if (Buffer != nullptr)
				{
					delete[] Buffer;
					Buffer = nullptr;
				}
				Buffer = new CHAR_INFO[BufferSize.X*BufferSize.Y];
				std::memcpy(Buffer, other.Buffer, sizeof(*Buffer)*BufferSize.X * BufferSize.Y);
				SetColor();
				return *this;
			}
		private:
			// Used for ConsoleWriteOutputW
			WorldSmallRect DrawArea;
			HANDLE ConsoleHandle;

			WORD ColorAttributes{};
			unsigned Attributes{};
			COORD CursorPosition{ 0, 0 };
			COORD BufferSize;
			CHAR_INFO* Buffer;



		protected:
			template <class T>
			static T Min(T const& in, T const& min)
			{
				return in > min ? in : min;
			}

			template <class T>
			static T Max(T const& in, T const& max)
			{
				return in < max ? in : max;
			}

			template <class T>
			static T Clamp(T const& in, T const& min, T const& max)
			{
				return Max(Min(in, min), max);
			}

		public:
			ConsoleOutput(const HANDLE consoleHandle, COORD const& bufferSize, WorldSmallRect const& drawArea)
				: DrawArea{ drawArea }
				, ConsoleHandle{ consoleHandle }, BufferSize{ bufferSize }
				, Buffer(new CHAR_INFO[bufferSize.X * bufferSize.Y])
			{
				std::memset(Buffer, 0, sizeof(CHAR_INFO) * BufferSize.X * BufferSize.Y);
				SetColor();
			}

			~ConsoleOutput() { delete[] Buffer; }

			enum TextAttributes
			{
				WORD_WRAP = 0x1,
			};

			struct CONSTANTS
			{
				RelativeCoord const TopLeft;
				RelativeCoord const TopCenter;
				RelativeCoord const TopRight;
				RelativeCoord const CenterLeft;
				RelativeCoord const CenterCenter;
				RelativeCoord const CenterRight;
				RelativeCoord const BottomLeft;
				RelativeCoord const BottomCenter;
				RelativeCoord const BottomRight;
			} const Constants{
				{0, 0}, {static_cast<SHORT>(BufferSize.X / 2), 0}, {static_cast<SHORT>(BufferSize.X - 1), 0},
				{0, static_cast<SHORT>(BufferSize.Y / 2)}, {static_cast<SHORT>(BufferSize.X / 2),
					static_cast<SHORT>(BufferSize.Y / 2)
				}, {static_cast<SHORT>(BufferSize.X - 1), static_cast<SHORT>(BufferSize.Y / 2)},
				{0, static_cast<SHORT>(BufferSize.Y - 1)}, {static_cast<SHORT>(BufferSize.X / 2),
					static_cast<SHORT>(BufferSize.Y - 1)
				}, {static_cast<SHORT>(BufferSize.X - 1), static_cast<SHORT>(BufferSize.Y - 1)}
			};

			constexpr WorldCoord ToWorld(RelativeCoord const& in) const
			{
				return { static_cast<SHORT>(in.X + DrawArea.Left), static_cast<SHORT>(in.Y + DrawArea.Top) };
			}

			constexpr RelativeCoord ToRelative(WorldCoord const& in) const
			{
				return { static_cast<SHORT>(in.X - DrawArea.Left), static_cast<SHORT>(in.Y - DrawArea.Top) };
			}

			void SetAttributes(unsigned const in)
			{
				Attributes = in;
			}

			void SetColor(WORD const in = P_DEFAULT)
			{
				ColorAttributes = in;
			}

			template <typename ...WORDS>
			void SetColor(WORD const in, WORDS const ... args)
			{
				SetColor(in);
				SetAttributes(args);
			}

			// DrawLine function adapted from https://github.com/OneLoneCoder/olcPixelGameEngine/
			void DrawLine(Line const& lineIn)
			{
				auto line{ lineIn };
				short x, y, xe, ye, i;
				const short dx = line.Right - line.Left;
				const short dy = line.Bottom - line.Top;

				const auto rol = [&](void)
				{
					line.Pattern = (line.Pattern << 1) | (line.Pattern >> 31);
					return line.Pattern & 1;
				};

				// straight lines idea by gurkanctn
				if (dx == 0) // Line is vertical
				{
					if (line.Bottom < line.Top) std::swap(line.Top, line.Bottom);
					for (y = line.Top; y <= line.Bottom; y++)
						if (rol()) Write(RelativeCoord{ line.Left, y }, line.Character);
					return;
				}

				if (dy == 0) // Line is horizontal
				{
					if (line.Right < line.Left) std::swap(line.Left, line.Right);
					for (x = line.Left; x <= line.Right; x++)
						if (rol()) Write(RelativeCoord{ x, line.Top }, line.Character);
					return;
				}

				// Line is Funk-aye
				const short dx1 = abs(dx);
				const short dy1 = abs(dy);
				short px = 2 * dy1 - dx1;
				short py = 2 * dx1 - dy1;
				if (dy1 <= dx1)
				{
					if (dx >= 0)
					{
						x = line.Left;
						y = line.Top;
						xe = line.Right;
					}
					else
					{
						x = line.Right;
						y = line.Bottom;
						xe = line.Left;
					}

					if (rol()) Write(RelativeCoord{ x, y }, line.Character);

					for (i = 0; x < xe; i++)
					{
						x = x + 1;
						if (px < 0) px = px + 2 * dy1;
						else
						{
							if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) y = y + 1;
							else y = y - 1;
							px = px + 2 * (dy1 - dx1);
						}
						if (rol()) Write(RelativeCoord{ x, y }, line.Character);
					}
				}
				else
				{
					if (dy >= 0)
					{
						x = line.Left;
						y = line.Top;
						ye = line.Bottom;
					}
					else
					{
						x = line.Right;
						y = line.Bottom;
						ye = line.Top;
					}

					if (rol()) Write(RelativeCoord{ x, y }, line.Character);

					for (i = 0; y < ye; i++)
					{
						y = y + 1;
						if (py <= 0) py = py + 2 * dx1;
						else
						{
							if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) x = x + 1;
							else x = x - 1;
							py = py + 2 * (dx1 - dy1);
						}
						if (rol()) Write(RelativeCoord{ x, y }, line.Character);
					}
				}
			}

			void DrawLine(Line const& line, unsigned const attributes)
			{
				auto const currentColor = ColorAttributes;
				SetColor(attributes);
				DrawLine(line);
				SetColor(currentColor);
			}

			void Fill(RelativeSmallRect const& area, wchar_t const character)
			{
				for (auto j = area.Top; j <= area.Bottom; j++)
				{
					// TODO: Use Draw Line Function
					SetCursorPosition(area.Left, j);
					for (auto i = area.Left; i <= area.Right; i++)
					{
						Write(character);
					}
				}
			}

			void Fill(RelativeSmallRect const& area, wchar_t const character, short const color)
			{
				auto const currentColor = ColorAttributes;
				SetColor(color);
				Fill(area, character);
				SetColor(ColorAttributes);
			}

			void Fill(RelativeCoord const& t1, RelativeCoord const& t2, wchar_t const character)
			{
				Fill(RelativeSmallRect{ t1.X, t1.Y, t2.X, t2.Y }, character);
			}

			void Fill(RelativeCoord const& t1, RelativeCoord const& t2, wchar_t const character, short const color)
			{
				Fill(RelativeSmallRect{ t1.X, t1.Y, t2.X, t2.Y }, character, color);
			}

			void Draw(Draw const& in) // Draw buffer to console
			{
				WorldSmallRect tempDraw{ DrawArea };
				WriteConsoleOutputW(ConsoleHandle, Buffer, BufferSize, { 0, 0 }, &tempDraw);
				if (in.Reset)
				{
					Fill({ 0, 0, BufferSize.X, BufferSize.Y }, L' ');
				}
			}

			void Draw(bool reset = false) // Draw buffer to console and reset it
			{
				Draw(Console::Draw{ reset });
			}

			template <class T>
			void Write(T const& in);
			void Write(const wchar_t* in);
			void Write(wchar_t const& in);


			template <class T, class ...Args>
			void Write(T const& in, Args const&... args)
			{
				Write(in);
				Write(args...);
			}

			void SetCursorPosition(RelativeCoord const& in)
			{
				if (in.X < 0 || in.Y < 0 || in.X >= BufferSize.X || in.Y >= BufferSize.Y)
				{
					throw std::out_of_range("Input is invalid.");
				}
				CursorPosition = in;
			}

			void SetCursorPosition(short const x, short const y)
			{
				SetCursorPosition({ x, y });
			}

			void SetCursorPosition() // DEFAULT
			{
				SetCursorPosition({ 0, 0 });
			}

			template <class T>
			ConsoleOutput& operator<<(T const& rhs)
			{
				Write(rhs);
				return *this;
			}
		};

		class OutputPane
		{
			HANDLE handle;
			SMALL_RECT Placement;
			bool Border{ false };
			CHAR_INFO BorderChar{};

		public:
			ConsoleOutput Out{ handle, {static_cast<SHORT>(Placement.Right - Placement.Left + 1), static_cast<SHORT>(Placement.Bottom - Placement.Top + 1) }, Placement };

			OutputPane(WorldSmallRect const& placement, HANDLE hnd)
				: handle{ hnd }
				, Placement{ placement }
			{
				DrawBorder();
			}

			OutputPane(WorldSmallRect const& placement, HANDLE hnd, CHAR_INFO const& borderChar)
				: handle{ hnd }
				, Placement{ placement }
				, Border{ true }
				, BorderChar{ borderChar }
			{
				DrawBorder();
			}

			OutputPane(OutputPane&& other) noexcept
				: handle{ other.handle }
				, Placement{ other.Placement }
				, Border{ other.Border }
				, BorderChar{ other.BorderChar }
				, Out{ other.Out }
			{
				DrawBorder();
			}

			void SetPaneColor(short const color)
			{
				Out.Fill({ 1, 1 }, Out.Constants.BottomRight - RelativeCoord{ 1, 1 }, L' ', color);
			}

			ConsoleOutput& operator*() { return Out; }
			ConsoleOutput* operator->() { return &Out; }

			void DrawBorder()
			{
				// TODO: use draw line function
				if (Border)
				{
					Out.SetColor(BorderChar.Attributes);
					Out.DrawLine({ 0, 0, static_cast<SHORT>(Placement.Right - Placement.Left), 0, 0xFFFFFFFF, BorderChar.Char.UnicodeChar});
					Out.DrawLine({ 0, static_cast<SHORT>(Placement.Bottom - Placement.Top), static_cast<SHORT>(Placement.Right - Placement.Left), 
						static_cast<SHORT>(Placement.Bottom - Placement.Top) ,0xFFFFFFFF, BorderChar.Char.UnicodeChar });
					Out.DrawLine({ 0, 1, 0, static_cast<SHORT>(Placement.Bottom - Placement.Top - 1) , 0xFFFFFFFF,BorderChar.Char.UnicodeChar });
					Out.DrawLine({ static_cast<SHORT>(Placement.Right - Placement.Left), 1, static_cast<SHORT>(Placement.Right - Placement.Left), 
						static_cast<SHORT>(Placement.Bottom - Placement.Top - 1), 0xFFFFFFFF , BorderChar.Char.UnicodeChar });
				}
			}

			void SetBorder(CHAR_INFO const& character)
			{
				Border = true;
				BorderChar = character;
				DrawBorder();
			}

			template <class T>
			OutputPane& operator<<(T const& in)
			{
				Out << in;
				return *this;
			}
		};

		class ConsoleHandler
		{
			std::vector<OutputPane> Panes{};
			unsigned CurrentPane{ 0 };
			const HANDLE ConsoleHandle;

		public:
			explicit ConsoleHandler(const HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE)) : ConsoleHandle(consoleHandle)
			{
				constexpr short left = 0;
				constexpr short top = 0;
				constexpr short right = 110;
				constexpr short bottom = 25;
				AddPane(WorldSmallRect{ left,top,right,bottom });
			}
			explicit ConsoleHandler(WorldSmallRect const& area, const HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE)) : ConsoleHandle(consoleHandle) {
				AddPane(area);
			}

			void ResizeConsole(WorldSmallRect const& area);

			void AddPane(WorldSmallRect const& area)
			{
				Panes.emplace_back(OutputPane{ area,ConsoleHandle });
			}
			void AddPane(WorldSmallRect const& area, CHAR_INFO const& border)
			{
				Panes.emplace_back(OutputPane{ area,ConsoleHandle,border });
			}

			void ChangeColor(short id, COLORREF color);

			void ChangeFont(std::wstring const& fontFamily = L"Courier New") const;

			void ResizeFont(const short width = 7, const short height = 14) const;

			OutputPane& operator[](unsigned const index)
			{
				if (index < 0U || index > Panes.size())
				{
					throw std::out_of_range("Index out of range");
				}
				CurrentPane = index;
				return Panes[CurrentPane];
			}

			template<class T>
			OutputPane& operator<<(T const& in)
			{
				return (Panes[CurrentPane] << in);
			}
		};
	}
}

/*
 *   TODO:
 *   Drawing pane,
 *   Scrolling pane,
 *   Container
 */
