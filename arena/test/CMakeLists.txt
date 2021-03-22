find_package(Catch2 REQUIRED)

add_executable(arena_test arena_test.cpp)
target_link_libraries(arena_test PRIVATE Catch2::Catch2 arena)

add_executable(arena_element_test arena_element_test.cpp)
target_link_libraries(arena_element_test PRIVATE Catch2::Catch2 arena)

add_executable(arena_benchmark arena_benchmark.cpp)
target_compile_options(arena_benchmark PRIVATE -masm=intel)
target_link_libraries(arena_benchmark PRIVATE Catch2::Catch2 arena)
