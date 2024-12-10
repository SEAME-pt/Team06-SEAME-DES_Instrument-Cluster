set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set (SOURCES_CORE_IMPL
)
add_library(speed-implementation SHARED ${SOURCES_CORE_IMPL})
add_library(speed::speed-implementation ALIAS speed-implementation)
target_include_directories(speed-implementation
    PUBLIC
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(speed-implementation PUBLIC speed::speed-api PRIVATE speed::speed-core Threads::Threads)
# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(speed-implementation PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(speed-implementation PRIVATE /W4 /WX /wd4251)
endif()

# add test cases
if(BUILD_TESTING)

find_package(Catch2 REQUIRED)

set (SOURCES_TEST
    ${CMAKE_CURRENT_SOURCE_DIR}/../generated/core/speed.test.cpp
)
add_executable(test_speed
    ${SOURCES_TEST}
)
target_link_libraries(test_speed speed::speed-implementation Catch2::Catch2)
target_include_directories(test_speed PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(test_speed PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(test_speed PRIVATE /W4 /WX /wd4251)
endif()

add_test(NAME test_speed COMMAND $<TARGET_FILE:test_speed>)
endif(BUILD_TESTING)

install(TARGETS speed-implementation
        EXPORT SpeedImplementationTargets)
# install includes
FILE(GLOB Speed_INCLUDES *.h)
install(FILES ${Speed_INCLUDES}
        DESTINATION include/speed/implementation)

export(EXPORT SpeedImplementationTargets
  NAMESPACE speed::
)

install(EXPORT SpeedImplementationTargets
  FILE SpeedImplementationTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE speed::
)
