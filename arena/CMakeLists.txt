add_library(arena include/arena/i_arena.h include/arena/arena.h)

set_target_properties(arena PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(
    arena PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                  $<INSTALL_INTERFACE:include>)

add_subdirectory(test)
