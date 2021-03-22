#include <iostream>
#define CATCH_CONFIG_MAIN
#include <arena/arena.h>
#include <catch2/catch.hpp>

SCENARIO("Arena Exhausted", "[Arena]") {

  GIVEN("an arena with two elements") {
    shrimp::arena::Arena<std::int32_t> arena;
    arena.initialize(2);

    WHEN("an element is created") {
      auto element = arena.create();
      THEN("it succeeds") {
        REQUIRE(element.get() != nullptr);
        WHEN("a second element is created") {
          auto element2 = arena.create();
          THEN("it succeeds") { REQUIRE(element2.get() != nullptr); }
          WHEN("a third element is created") {
            auto element3 = arena.create();
            THEN("it fails") { REQUIRE(element3.get() == nullptr); }
          }
        }
      }
    }
  }
}

SCENARIO("Arena elements are returned", "[Arena]") {

  GIVEN("an arena with two elements") {
    shrimp::arena::Arena<std::int32_t> arena;
    arena.initialize(2);

    std::int32_t i{GENERATE(range(1, 10))};

    WHEN("an element is created") {
      auto element = arena.create();
      THEN("it succeeds") {
        REQUIRE(element.get() != nullptr);
        *element = i;
      }
    }
  }
}

SCENARIO("Arena elements are returned and exhausted", "[Arena]") {

  GIVEN("an arena with two elements") {
    shrimp::arena::Arena<std::int32_t> arena;
    arena.initialize(2);

    std::int32_t i{GENERATE(range(1, 10))};

    WHEN("an element is created") {
      auto element = arena.create();
      THEN("it succeeds") {
        REQUIRE(element.get() != nullptr);
        *element = i;
        WHEN("an element2 is created") {
          auto element2 = arena.create();
          THEN("it succeeds") {
            REQUIRE(element2.get() != nullptr);
            *element2 = i;
            WHEN("an element3 is created") {
              auto element3 = arena.create();
              THEN("it fails") { REQUIRE(element3 == nullptr); }
            }
          }
        }
      }
    }
  }
}