cmake_minimum_required(VERSION 3.17)
project(MersenneTwister)

set(CMAKE_CXX_STANDARD 11)

if(MSVC)
  add_compile_options(/W4)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()
 
# biblioteka
add_library(mersenne_twister INTERFACE)
target_include_directories(mersenne_twister INTERFACE src/)

# testy
enable_testing()
add_subdirectory(catch)
add_executable(tests
  tests.cpp
)
target_link_libraries(tests PRIVATE catch2)
target_link_libraries(tests PRIVATE mersenne_twister)
add_test(tests tests)

# demo
add_executable(liczby_losowe
  liczby_losowe.cpp
)
target_link_libraries(liczby_losowe PRIVATE mersenne_twister)
