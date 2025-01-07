find_package(GTest REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/src)

add_executable(ConnectionProtocolTest ConnectionProtocolTest.cpp)

target_link_libraries(ConnectionProtocolTest PRIVATE GTest::GTest GTest::Main ConnectionProtocolLib)

add_test(NAME ConnectionProtocolTest COMMAND ConnectionProtocolTest)