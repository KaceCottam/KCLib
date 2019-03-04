#pragma once

#include <ctime>
#include <conio.h>

namespace KC
{
	namespace Controller
	{
		enum class InputFlag : int
		{
			FlagReturn,
			FlagEscape,
			FlagNumpad,
			FlagNormal,
			FlagKeyReturn = 224
		};

		enum InputKey : int
		{
			// taken from Windows.h

			VK_LBUTTON =0x01,
			VK_RBUTTON =0x02,
			VK_CANCEL =0x03,
			VK_MBUTTON =0x04,
			VK_BACK =0x08,
			VK_TAB =0x09,
			VK_CLEAR =0x0C,
			VK_RETURN =0x0D,
			VK_SHIFT =0x10,
			VK_CONTROL =0x11,
			VK_MENU =0x12,
			VK_PAUSE =0x13,
			VK_CAPITAL =0x14,
			VK_FINAL =0x18,
			VK_ESCAPE =0x1B,
			VK_CONVERT =0x1C,
			VK_NONCONVERT =0x1D,
			VK_ACCEPT =0x1E,
			VK_MODECHANGE =0x1F,
			VK_SPACE =0x20,
			VK_PRIOR =0x21,
			VK_NEXT =0x22,
			VK_END =0x23,
			VK_HOME =0x24,
			VK_LEFT =0x25,
			VK_UP =0x26,
			VK_RIGHT =0x27,
			VK_DOWN =0x28,
			VK_SELECT =0x29,
			VK_PRINT =0x2A,
			VK_EXECUTE =0x2B,
			VK_SNAPSHOT =0x2C,
			VK_INSERT =0x2D,
			VK_DELETE =0x2E,
			VK_HELP =0x2F,
			VK_LWIN =0x5B,
			VK_RWIN =0x5C,
		};

		inline auto Ctrl(int key) -> int;

		inline auto KeyF(int key) -> int;

		inline auto CtrlKeyF(int key) -> int;

		auto GetKey(InputFlag& flag, time_t delay = 0) -> int;
	}
}
