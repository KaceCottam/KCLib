#pragma once


namespace KC
{
	class Controller final
	{
	public:
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

			LButton =0x01,
			RButton =0x02,
			Cancel =0x03,
			MButton =0x04,
			Back =0x08,
			Tab =0x09,
			Clear =0x0C,
			Return =0x0D,
			Shift =0x10,
			Control =0x11,
			Menu =0x12,
			Pause =0x13,
			Capital =0x14,
			Final =0x18,
			Escape =0x1B,
			Convert =0x1C,
			Nonconvert =0x1D,
			Accept =0x1E,
			ModeChange =0x1F,
			Space =0x20,
			Prior =0x21,
			Next =0x22,
			End =0x23,
			Home =0x24,
			Left =0x25,
			Up =0x26,
			Right =0x27,
			Down =0x28,
			Select =0x29,
			Print =0x2A,
			Execute =0x2B,
			Snapshot =0x2C,
			Insert =0x2D,
			Delete =0x2E,
			Help =0x2F,
			LWin =0x5B,
			RWin =0x5C,
		};

		static int Ctrl(int key);

		static int KeyF(int key);

		static int CtrlKeyF(int key);

		static int GetKey(InputFlag& flag, int delay = 0);
	};
}
