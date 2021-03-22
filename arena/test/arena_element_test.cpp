#include <arena/arena_element.h>
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <iostream>
#include <vector>

SCENARIO("move_front", "[ArenaElement]") {

  GIVEN("an inialized vector of arena elements pointing at integers") {
    std::vector<std::int32_t> integers{1, 2, 3};
    std::vector<shrimp::arena::detail::ArenaElement<std::int32_t>> elements{};

    for (auto &i : integers) {
      elements.emplace_back(shrimp::arena::detail::ArenaElement<std::int32_t>{
          &integers[i], nullptr});
    }

    elements[0].next = &elements[1];
    elements[1].next = &elements[2];
    elements[2].next = nullptr;

    GIVEN("a filled source and empty target list") {
      shrimp::arena::detail::ArenaElement<std::int32_t> *src_list{&elements[0]};
      shrimp::arena::detail::ArenaElement<std::int32_t> *tgt_list{nullptr};
      WHEN("calling move_front") {
        auto elem =
            shrimp::arena::detail::ArenaElement<std::int32_t>::move_front(
                src_list, tgt_list);

        THEN("move_front returns a pointer to front of former src_list head") {
          REQUIRE(elem->t == &integers[0]);
          REQUIRE(tgt_list->t == &integers[0]);
          REQUIRE(src_list->t == &integers[1]);

          WHEN("calling move_front with switched lists") {
            auto elem =
                shrimp::arena::detail::ArenaElement<std::int32_t>::move_front(
                    tgt_list, src_list);

            THEN("move_front returns a pointer to front of former tgt_list "
                 "head") {
              REQUIRE(elem->t == &integers[0]);
              REQUIRE(tgt_list == nullptr);
              REQUIRE(src_list->t == &integers[0]);
            }
          }
        }
      }

      WHEN("calling move_front on empty tgt_list ") {
        auto elem =
            shrimp::arena::detail::ArenaElement<std::int32_t>::move_front(
                /*source*/ tgt_list, /*target*/ src_list);
        THEN("nothing is moved") {
          REQUIRE(elem == nullptr);
          REQUIRE(tgt_list == nullptr);
          REQUIRE(src_list->t == &integers[0]);
        }
      }
    }
  }
} // namespace detail