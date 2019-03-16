//#comment file
#include <KCConsole.hpp>

class Console : public KC::Console::ConsoleEngine
{
protected:
	bool OnUserCreate() override
	{
		RegisterKeyHandler("enter",VK_RETURN);
		return true;
	}
	bool OnUserUpdate(float dTime) override
	{
		DrawLine(0,0,ScreenSize.X,ScreenSize.Y,KC::Console::PixelSolid,"blue");
		if(GetKeyState("enter").Held)
			return false;
		return true;
	}
};

int main()
{
	Console mainConsole;
	mainConsole.ConstructConsole({120,40},{8,8});
	mainConsole.Start();
	return 0;
}