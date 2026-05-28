cmake_minimum_required(VERSION 3.14)

project(SecondLab)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(route_lib
    src/stop.cpp
    src/base64.cpp
)

target_include_directories(route_lib PUBLIC include)

add_executable(bus_route
    src/main.cpp
)

target_link_libraries(bus_route PRIVATE route_lib)

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

FetchContent_MakeAvailable(googletest)

add_executable(route_tests
    tests/tests.cpp
)

target_link_libraries(route_tests
    PRIVATE
    route_lib
    gtest
    gtest_main
)

enable_testing()

add_test(NAME RouteTests COMMAND route_tests)