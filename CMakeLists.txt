cmake_minimum_required(VERSION 3.14)
project(ConnectionProtocol)

set(CMAKE_CXX_STANDARD 14)

enable_testing()

set(sources
    Main.cpp
    src/ConnectionProtocol.cpp
    test/ConnectionProtocolTest.cpp)

include_directories(src/)

add_executable(ConnectionProtocolTest ${sources})

find_package(GTest CONFIG REQUIRED)

target_link_libraries(
    ConnectionProtocolTest
    GTest::gmock_main
    GTest::gtest
)

include(GoogleTest)
gtest_discover_tests(ConnectionProtocolTest)