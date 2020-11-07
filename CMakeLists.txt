cmake_minimum_required(VERSION 3.17)
project(MersenneTwister)

set(CMAKE_CXX_STANDARD 14)

if(MSVC)
  add_compile_options(/W4)
else()
  add_compile_options(-Wall -Wextra -pedantic)
endif()
 
# biblioteka
add_library(mersenne_twister
  src/mersenne_twister/mersenne_twister.cpp
  src/mersenne_twister/mersenne_twister.hpp
)
target_include_directories(mersenne_twister INTERFACE src/)

# testy jednostkowe
enable_testing()
add_subdirectory(catch)
add_executable(tests
  tests.cpp
)
target_link_libraries(tests PRIVATE catch2)
target_link_libraries(tests PRIVATE mersenne_twister)
add_test(tests tests)
