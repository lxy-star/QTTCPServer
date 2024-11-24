# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\TCPServer_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\TCPServer_autogen.dir\\ParseCache.txt"
  "TCPServer_autogen"
  )
endif()
