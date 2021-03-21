add_executable(arena_test arena_test.cpp)

find_package(Catch2 REQUIRED)

target_link_libraries(arena_test PRIVATE Catch2::Catch2)