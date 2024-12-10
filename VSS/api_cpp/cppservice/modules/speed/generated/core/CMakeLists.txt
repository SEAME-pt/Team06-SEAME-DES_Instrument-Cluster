set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(nlohmann_json REQUIRED)
set (SOURCES_CORE_SUPPORT
    speed.json.adapter.cpp
)
add_library(speed-core SHARED ${SOURCES_CORE_SUPPORT})
add_library(speed::speed-core ALIAS speed-core)
target_include_directories(speed-core
    PUBLIC
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(speed-core PUBLIC speed::speed-api nlohmann_json::nlohmann_json)
# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(speed-core PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(speed-core PRIVATE /W4 /WX /wd4251)
endif()

install(TARGETS speed-core
        EXPORT SpeedCoreTargets)
# install includes
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include/speed/generated FILES_MATCHING PATTERN "*.h")

export(EXPORT SpeedCoreTargets
  NAMESPACE speed::
)

install(EXPORT SpeedCoreTargets
  FILE SpeedCoreTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE speed::
)
