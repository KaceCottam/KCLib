cmake_minimum_required(VERSION 3.8)

function(add_kc_test TARGET TEST_TARGET)
  project(${TARGET})

  add_test(${TARGET} ${TARGET}.cpp)
  add_executable(${TARGET} ${TARGET}.cpp)

  target_include_directories(${TARGET} PRIVATE ${CMAKE_SOURCE_DIR}/src .)

  message("Added KC test: " ${TARGET} " testing " ${TEST_TARGET} " (" ${${TEST_TARGET}_VERSION} ")")
endfunction(add_kc_test)

add_kc_test(TestLists KCLists)
# add_subdirectory(TestKCQueues) 
# add_subdirectory(TestKCStateMachine)
# add_subdirectory(TestKCBinarySearchTree)
# add_subdirectory(TestKCStacks)
