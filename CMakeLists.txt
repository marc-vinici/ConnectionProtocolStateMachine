cmake_minimum_required(VERSION 3.14)
project(ConnectionProtocol)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${PROJECT_SOURCE_DIR}/src)

add_library(ConnectionProtocolLib ${PROJECT_SOURCE_DIR}/src/ConnectionProtocol.cpp)

add_executable(ConnectionProtocol Main.cpp)

target_link_libraries(ConnectionProtocol ConnectionProtocolLib)

enable_testing()

add_subdirectory(test)
