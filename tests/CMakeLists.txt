cmake_minimum_required(VERSION 3.8)

set(Tests_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/tests)

add_subdirectory(TestKCLinkedLists)
add_subdirectory(TestKCQueues) 
add_subdirectory(TestKCStateMachine)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/RunAllTests.bat DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})