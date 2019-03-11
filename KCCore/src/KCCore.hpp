#pragma once

#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif // !ENABLE_VIRTUAL_TERMINAL_PROCESSING

namespace KC
{
	class Core final
	{
	public:
		static unsigned int RandomizationSeed;
		static void EnableConsoleColor();
		static void ResizeCursor(unsigned int visible = 0);
		static void SetupKCLib();
	};
}
