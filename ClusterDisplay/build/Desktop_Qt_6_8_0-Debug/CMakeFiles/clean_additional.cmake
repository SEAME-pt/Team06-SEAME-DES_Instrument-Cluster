# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/appClusterDisplay_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/appClusterDisplay_autogen.dir/ParseCache.txt"
  "appClusterDisplay_autogen"
  )
endif()
