# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project(KCLib VERSION 4.0)

option(COMPILE_SOURCES ON)
option(COMPILE_TESTS OFF)
option(COMPILE_EXAMPLES OFF)

if(COMPILE_SOURCES)
  add_subdirectory(src)
endif()

if(COMPILE_TESTS)
  add_subdirectory(tests)
endif()

if(COMPILE_EXAMPLES)
  add_subdirectory(examples/SimpleBSTShowcase)
  add_subdirectory(examples/SimpleCSVParserShowcase)
endif()
