set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_library(speed-api INTERFACE)
add_library(speed::speed-api ALIAS speed-api)
target_include_directories(speed-api
    INTERFACE
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)

# install binary files
install(TARGETS speed-api
        EXPORT SpeedApiTargets)
# install includes
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include/speed/generated FILES_MATCHING PATTERN "*.h")

export(EXPORT SpeedApiTargets
  NAMESPACE speed::
)

install(EXPORT SpeedApiTargets
  FILE SpeedApiTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE speed::
)
