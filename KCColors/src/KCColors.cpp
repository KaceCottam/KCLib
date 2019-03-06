#include "KCColors.hpp"
#include <iostream>

void KC::Colors::Colorize(char* color, const std::function<void()>& function)
{
	std::cout << color;
	function();
	std::cout << reset;
}
