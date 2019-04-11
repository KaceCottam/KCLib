#define CATCH_CONFIG_MAIN
#include <Catch2/catch.hpp>
#include <KCLib/KCLists.hpp>
#include <vector>

TEST_CASE("Simple list<int>","[list]") {
  kc::list<int> test_list{};
  std::vector<int> test_vector{};
  SECTION("empty constructor") {
    test_list = kc::list<int>{};
    test_vector = std::vector<int>{};
    REQUIRE(test_list.empty());
    REQUIRE(test_list.size() == test_vector.size());
  }
  SECTION("constructor with one item") {
    test_list = kc::list<int>{0};
    test_vector = std::vector<int>{0};
    REQUIRE(!test_list.empty());
    REQUIRE(test_list.size() == test_vector.size());
  }
  SECTION("constructor with multiple items") {
    test_list = kc::list<int>{0,1,2,3};
    test_vector = std::vector<int>{0,1,2,3};
    REQUIRE(!test_list.empty());
    REQUIRE(test_list.size() == test_vector.size());
  }

  SECTION("push with one item") {
    test_list.push(1);
    test_vector.emplace(test_vector.cbegin(), 1);
    REQUIRE(test_list.size() == test_vector.size());
    REQUIRE(*test_list.begin() == 1);
  }

  SECTION("push with many items") {
    test_list.push(1,2,3);
    test_vector.emplace(test_vector.cbegin(), 1);
    test_vector.emplace(test_vector.cbegin(), 2);
    test_vector.emplace(test_vector.cbegin(), 3);
    REQUIRE(test_list.size() == test_vector.size());
    REQUIRE(*test_list.begin() == 3);
  }
}
