cmake_minimum_required(VERSION 3.20)
project(speed)

# needed to access CMAKE_INSTALL_LIBDIR
include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_BINARY_DIR})
set(InstallDir ${CMAKE_INSTALL_LIBDIR}/cmake/speed)

# enable testing
if(BUILD_TESTING)
include(CTest)
enable_testing()
endif(BUILD_TESTING)

# define variable for library include paths
get_filename_component(MODULES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/.." ABSOLUTE)

add_subdirectory(generated/api)
add_subdirectory(generated/core)

include(CMakePackageConfigHelpers)
configure_package_config_file(SpeedConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/speedConfig.cmake
  INSTALL_DESTINATION ${InstallDir})
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/speedConfigVersion.cmake
  VERSION 1.0
  COMPATIBILITY SameMinorVersion )
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/speedConfig.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/speedConfigVersion.cmake
        DESTINATION ${InstallDir} )
