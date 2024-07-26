cmake_minimum_required(VERSION 3.20)
project(fallmento)

set(CMAKE_CXX_STANDARD 17)

# note msvc dont support computed goto statement
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang)

# clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(./ ./test)

add_executable(testOrigin ./test/testOrigin.cc)
add_executable(testOptimize ./test/testOptimize.cc)
add_executable(testOptimize2 ./test/testOptimize2.cc)
add_executable(testMultyield ./test/testMultyield.cc)
add_executable(testPrimefactor ./test/testPrimefactor.cc)

# file(GLOB sources CONFIGURE_DEPENDS src/*.cc src/*.h test/*.cc test/*.h)

# message("sources: "${sources})
# target_sources(main PUBLIC ${sources})