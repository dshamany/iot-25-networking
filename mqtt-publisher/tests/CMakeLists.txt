cmake_minimum_required(VERSION 3.16)
project(mqtt-publisher-tests CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)

add_executable(sensor_tests
    sensor_unittest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../main/sensor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../utils/timestamp.cpp
)

target_include_directories(sensor_tests
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../main
    ${CMAKE_CURRENT_SOURCE_DIR}/../utils
)

target_link_libraries(sensor_tests
    PRIVATE
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(sensor_tests)
