#define CATCH_CONFIG_MAIN
#include <Catch2/catch.hpp>
#include <KCLib/KCLists.hpp>
#include <vector>

TEST_CASE("Simple list<int> with default constructor", "[list]") {
  kc::list<int> test_list{};
  SECTION("empty constructor") {
    test_list = kc::list<int>{};
    REQUIRE(test_list.empty());
    REQUIRE(test_list.size() == 0);
    SECTION("push with one item") {
      test_list.push(1);
      REQUIRE(test_list.size() == 1);
      REQUIRE(*test_list.begin() == 1);
    }
    SECTION("push with many items") {
      test_list.push(1, 2, 3);
      REQUIRE(test_list.size() == 3);
      REQUIRE(*test_list.begin() == 3);
      REQUIRE(*(test_list.begin()+=1) == 2);
      REQUIRE(*(test_list.begin()+=2) == 1);
      REQUIRE((test_list.begin()+=3).current_node == nullptr);

      SECTION("pop/pop_back are correct") {
        int test_variable;
        test_list.pop(test_variable);
        REQUIRE(test_list.size() == 2);
        REQUIRE(test_variable == 3);

        test_list.pop_back(test_variable);
        REQUIRE(test_list.size() == 1);
        REQUIRE(test_variable == 1);
      }
    }
  }
}

TEST_CASE("Simple list<int> with constructor of 1 item", "[list]") {
  kc::list<int> test_list{};
  SECTION("constructor with one item") {
    test_list = kc::list<int>{0};
    REQUIRE(!test_list.empty());
    REQUIRE(test_list.size() == 1);
  }
}

TEST_CASE("simple list<int> with constructor of multiple items", "[list]") {
  kc::list<int> test_list{};
  SECTION("constructor with multiple items") {
    test_list = kc::list<int>{0, 1, 2, 3};
    REQUIRE(!test_list.empty());
    REQUIRE(test_list.size() == 4);
  }
}