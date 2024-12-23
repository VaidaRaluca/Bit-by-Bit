# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Eter_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Eter_autogen.dir\\ParseCache.txt"
  "Eter_autogen"
  )
endif()
