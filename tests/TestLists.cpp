#define CATCH_CONFIG_MAIN
#include <Catch2/catch.hpp>
#include <KCLib/KCLists.hpp>

TEST_CASE("Simple list<int>")
{
  SECTION("Test empty constructor")
  {
    kc::list<int> testList{};
    REQUIRE(testList.empty());
  }
  SECTION("Test constructor of multiple elements")
  {
    kc::list<int> testList{5,4,3,2,1};
    REQUIRE(!testList.empty());

    SECTION("Elements are in the right place");
    for(auto i = 1; i < 6; ++i)
    {
      REQUIRE(testList[i-1] == i);
    }
  }
}