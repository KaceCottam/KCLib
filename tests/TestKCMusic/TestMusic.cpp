#include <Test.h>
#include <KCMusic.hpp>

TEST_CASE("Music is correctly linked")
{
	REQUIRE(KC::Music::FetchTone(4, 'C') == 261);
}
