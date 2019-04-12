# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project(KCLib VERSION 4.0)

option(COMPILE_SOURCES ON)
option(COMPILE_TESTS OFF)
option(COMPILE_EXAMPLES OFF)
option(CODE_COVERAGE ON)

if(COMPILE_SOURCES)
  add_subdirectory(src)
endif()

if(CODE_COVERAGE)
  list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
  set(COVERAGE_GCOVR_EXCLUDES "${CMAKE_SOURCE_DIR}/tests/Catch2")
  include(CodeCoverage REQUIRED)
  APPEND_COVERAGE_COMPILER_FLAGS()
endif()

if(COMPILE_TESTS)
  add_subdirectory(tests)
endif()

if(COMPILE_EXAMPLES)
  add_subdirectory(examples/SimpleBSTShowcase)
  add_subdirectory(examples/SimpleCSVParserShowcase)
endif()
