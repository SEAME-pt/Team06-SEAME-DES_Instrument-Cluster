cmake_minimum_required(VERSION 2.8.12)

project(ClusterDisplay LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(HEADERS
    inc/TestBattery.hpp inc/TestSpeedSensor.hpp)

include_directories(inc)

find_package(Qt5 COMPONENTS Core Quick REQUIRED)

add_executable(${PROJECT_NAME}
        ${HEADERS}
        main.cpp qml.qrc
        TestBattery.cpp TestSpeedSensor.cpp)

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Quick pthread)
