#include <Test.h>
#include <KCController.hpp>

TEST_CASE("Controller is linked")
{
	REQUIRE(KC::Controller::Up == VK_UP);
}