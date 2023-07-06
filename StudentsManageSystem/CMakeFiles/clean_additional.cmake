# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\EasyChat_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\EasyChat_autogen.dir\\ParseCache.txt"
  "EasyChat_autogen"
  )
endif()
