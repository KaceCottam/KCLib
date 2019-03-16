#pragma once
#define _WIN32_WINNT 0x0500
#include <Windows.h>
#include <unordered_map>
#include <string>
#include <atomic>
#include <mutex>
#include <functional>

// A majority of this code is taken from https://github.com/OneLoneCoder/olcPixelGameEngine

namespace KC
{
	namespace Console
	{
		struct ColorRGB
		{
			union
			{
				struct
				{
					WORD A;
					WORD B;
					WORD G;
					WORD R;
				};

				COLORREF Value = 0x00FFFFFF;
			};

			ColorRGB(WORD r, WORD g, WORD b);
		};

		enum PixelType
		{
			PixelSolid = 0x2588,
			PixelThreeQuarters = 0x2593,
			PixelHalf = 0x2592,
			PixelQuarter = 0x2591,
			PixelLightShade = 0x2591,
			PixelMediumShade = 0x2592,
			PixelDarkShade = 0x2593,
		};


		class ConsoleEngine
		{
		protected:
			CHAR_INFO* BufferText;
			COORD ScreenSize;
			std::wstring AppName;
			HANDLE OriginalConsole;
			CONSOLE_SCREEN_BUFFER_INFO OriginalConsoleInfo;
			HANDLE Console;
			HANDLE ConsoleIn;
			SMALL_RECT RectWindow;
			COORD LastWritePosition;

			// These need to be static because of the OnDestroy call the OS may make. The OS
			// spawns a special thread just for that
			static std::atomic<bool> AtomActive;
			static std::condition_variable GameFinished;
			static std::mutex GameThreadMutex;
		private:
			std::unordered_map<std::string, BYTE> ColorLookup;
			std::unordered_map<std::string, WORD> KeyLookup;
			std::unordered_map<std::string, int> KeyIdentifierLookup;

			struct Pixel
			{
				WORD Attributes;
				wchar_t Character;
			};

			std::unordered_map<std::string, Pixel> PixelAliasLookup;

			void GameThread();

		protected :
			ConsoleEngine();

			~ConsoleEngine();

			virtual bool OnUserCreate() = 0;
			virtual bool OnUserUpdate(float dTime) = 0;
			virtual bool OnUserDestroy() { return true; }

			void RegisterColor(std::string const& identifier, BYTE colorTablePosition, int r, int b, int g);
			void RegisterColor(std::string const& identifier, BYTE colorTablePosition, ColorRGB const& color);
			void ChangeColor(std::string const& identifier, ColorRGB const& color);
			void ChangeColor(std::string const& identifier, int r, int b, int g);
			void RegisterColorAlias(std::string const& oldIdentifier, std::string const& newIdentifier);
			void RegisterPixelAlias(std::string const& identifier, std::string const& foregroundColor, wchar_t c);
			void RegisterKeyHandler(std::string const& identifier, WORD character);

			struct KeyState
			{
				bool Held;
			};

			KeyState* Keys;
			KeyState GetKeyState(std::string const& identifier);
			virtual void Draw(int x, int y, std::string const& pixelIdentifier);
			virtual void Draw(int x, int y, wchar_t c, std::string const& foregroundColor);
			void DrawLine(int left, int top, int right, int bottom, wchar_t c, std::string const& foregroundColor,
			              float weight = 0.0f);
			void DrawLine(int left, int top, int right, int bottom, std::string const& pixelIdentifier,
			              float weight = 0.0f);
			void Clip(int& x, int& y) const;
			void Fill(int left, int top, int right, int bottom, std::string const& pixelIdentifier);
			void Fill(int left, int top, int right, int bottom, wchar_t c, std::string const& foregroundColor);
			void DrawRect(int left, int top, int right, int bottom, wchar_t c, std::string const& foregroundColor,
			              float weight = 0.0f);
			void DrawRect(int left, int top, int right, int bottom, std::string const& pixelIdentifier,
			              float weight = 0.0f);
			void DrawString(int x, int y, std::wstring const& s, std::string const& foregroundColor);
			void DrawString(std::wstring const& s, std::string const& foregroundColor);
			template <class T, class... Args>
			void Write(T first, Args ... args, std::string const& foregroundColor);
			template <class T, class... Args>
			void Write(int x, int y, T first, Args ... args, std::string const& foregroundColor);
			void DrawStringAlpha(int x, int y, std::wstring const& s, std::string const& foregroundColor);

		public:
			int ConstructConsole(COORD const& bufSize, COORD const& fontSize);
			int ConstructConsole();
			void Start();
		};

		template <class T, class ... Args>
		void ConsoleEngine::Write(T first, Args ... args, std::string const& foregroundColor)
		{
			DrawString(first, foregroundColor);
			Write(args..., foregroundColor);
		}

		template <class T, class ... Args>
		void ConsoleEngine::Write(int x, int y, T first, Args ... args, std::string const& foregroundColor)
		{
			DrawString(x, y, first, foregroundColor);
			Write(args..., foregroundColor);
		}
	}
}
