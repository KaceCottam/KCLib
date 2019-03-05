#include <Test.h>
#include <KCColors.hpp>

TEST_CASE("Colors included")
{
	REQUIRE(KC::Colors::reset == "\x1b[0m");
}
