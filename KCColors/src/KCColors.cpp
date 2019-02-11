#include "KCColors.h"
#include <iostream>

auto KC::Colors::Colorize(char* color, const std::function<void()>& function) -> void
{
	std::cout << color;
	function();
	std::cout << reset;
}
