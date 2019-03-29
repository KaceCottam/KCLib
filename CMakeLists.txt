# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project (KCLib)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(KCLIB_HEADER_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(KCConsole_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src/KCConsole)
set(KCStateMachine_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src/KCStateMachine)
set(KCNodes_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src/KCNodes)
set(KCLinkedLists_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src/KCLinkedLists)
set(KCQueues_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src/KCQueues)
set(KCMusic_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src/KCMusic)
set(KCBinarySearchTree_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src/KCBinarySearchTree)
set(KCStacks_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src/KCStacks)
set(KCCSVParser_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src/KCCSVParser)

add_subdirectory(src)

add_subdirectory(tests)
