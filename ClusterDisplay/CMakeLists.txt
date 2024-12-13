cmake_minimum_required(VERSION 3.10.2)

project(ClusterDisplay VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.5)

#target_sources(appClusterDisplay
#  PRIVATE
#    Speedometer.qml
#)

qt_add_executable(appClusterDisplay
    main.cpp
)

qt_add_qml_module(appClusterDisplay
    URI ClusterDisplay
    VERSION 1.0
    QML_FILES
        Main.qml
        SOURCES TestBattery.hpp TestBattery.cpp
        SOURCES BatteryIconObj.hpp BatteryIconObj.cpp
        QML_FILES BatteryIcon.qml
        QML_FILES SimpleBar.qml
        RESOURCES qml.qrc
        SOURCES TestSpeedSensor.hpp TestSpeedSensor.cpp
        SOURCES SpeedometerObj.hpp SpeedometerObj.cpp
        QML_FILES Speedometer.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appClusterDisplay PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appClusterDisplay
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appClusterDisplay
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appClusterDisplay
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
