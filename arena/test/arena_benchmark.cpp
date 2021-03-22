#include <iostream>
#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include <arena/arena.h>
#include <catch2/catch.hpp>

class Complex {
public:
  Complex() = default;

  std::array<std::uint8_t, 1500> buffer;
};

// using BaseType = std::int32_t;
using BaseType = Complex;
using Arena = shrimp::arena::Arena<BaseType>;
constexpr std::int32_t CYCLES{100000};

std::int32_t many_allocations_with(Arena &arena) {
  std::int32_t sum{0};
  for (auto i = 0; i < CYCLES; i++) {
    auto tmp = arena.create();
    tmp->buffer[0] += i;
    sum += tmp->buffer[0];
  }
  return sum;
}

std::int32_t many_allocations_heap() {
  std::int32_t sum{0};
  for (auto i = 0; i < CYCLES; i++) {
    auto tmp = new BaseType;
    tmp->buffer[0] += i;
    sum += tmp->buffer[0];
    delete tmp;
  }
  return sum;
}

TEST_CASE("Benchmarks", "[Arena]") {

  Arena arena;
  arena.initialize(2);

  BENCHMARK("Heap allocations with new/delete") {
    return many_allocations_heap();
  };
  BENCHMARK("Heap allocations with arena") {
    return many_allocations_with(arena);
  };
}