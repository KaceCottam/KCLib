#ifndef KC_COLORS_H
#define KC_COLORS_H
#include <functional>
namespace KC
{
	namespace Colors
	{
		const char* deleteLine = "\33[2K\r";
		const char* cursorUp = "\33[1A";
		const char* cursorDown = "\33[1B";
		const char* cursorRight = "\33[1C";
		const char* cursorLeft = "\33[1D";
		const char* bold = "\x1b[1m";
		const char* underline = "\x1b[4m";
		const char* inverse = "\x1b[7m";
		const char* reset = "\x1b[0m";
		namespace Weak
		{
			const char* black = "\x1b[30m";
			const char* red = "\x1b[31m";
			const char* green = "\x1b[32m";
			const char* yellow = "\x1b[33m";
			const char* blue = "\x1b[34m";
			const char* magenta = "\x1b[35m";
			const char* cyan = "\x1b[36m";
			const char* white = "\x1b[37m";
		}

		namespace Strong
		{
			const char* black = "\x1b[90m";
			const char* red = "\x1b[91m";
			const char* green = "\x1b[92m";
			const char* yellow = "\x1b[93m";
			const char* blue = "\x1b[94m";
			const char* magenta = "\x1b[95m";
			const char* cyan = "\x1b[96m";
			const char* white = "\x1b[97m";
		}

		auto Colorize(char* color, const std::function<void()>& function) -> void;

	}
	namespace Highlights
	{
		namespace Weak
		{
			const char* black = "\x1b[40m";
			const char* red = "\x1b[41m";
			const char* green = "\x1b[42m";
			const char* yellow = "\x1b[43m";
			const char* blue = "\x1b[44m";
			const char* magenta = "\x1b[45m";
			const char* cyan = "\x1b[46m";
			const char* white = "\x1b[47m";
		}

		namespace Strong
		{
			const char* black = "\x1b[100m";
			const char* red = "\x1b[101m";
			const char* green = "\x1b[102m";
			const char* yellow = "\x1b[103m";
			const char* blue = "\x1b[104m";
			const char* magenta = "\x1b[105m";
			const char* cyan = "\x1b[106m";
			const char* white = "\x1b[107m";
		}
	}
}


#endif // !KC_COLORS_H
