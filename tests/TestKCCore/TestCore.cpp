#include <Test.h>
#include <KCCore.hpp>

SCENARIO("Link with KCCore")
{
	KC::Core::randomizationSeed = 0;
	REQUIRE(KC::Core::randomizationSeed == 0);
}