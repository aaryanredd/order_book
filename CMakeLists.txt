cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)
project(order_book_lib VERSION 1.0.1 DESCRIPTION "Order Book Project")

add_subdirectory(src)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/nlohmann/include ${CMAKE_CURRENT_SOURCE_DIR}/src/include)

add_executable(benchmarks ${CMAKE_CURRENT_SOURCE_DIR}/benchmarks.cpp)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/benchmark)

target_link_libraries(benchmarks PRIVATE order_book benchmark::benchmark )

add_executable(tests ${CMAKE_CURRENT_SOURCE_DIR}/tests/tests.cpp)
target_link_libraries(tests PRIVATE order_book gtest gtest_main)

