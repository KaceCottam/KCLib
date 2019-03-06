#pragma once

#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif // !ENABLE_VIRTUAL_TERMINAL_PROCESSING

namespace KC
{
	namespace Core
	{
		static unsigned int randomizationSeed;
		void EnableConsoleColor();
		void ResizeCursor(unsigned int visible = 0);
		void SetupKCLib();
	}
}
