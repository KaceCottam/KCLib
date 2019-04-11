cmake_minimum_required(VERSION 3.8)

include(CTest)

if(CODE_COVERAGE)
  list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
  include(CodeCoverage REQUIRED)
  APPEND_COVERAGE_COMPILER_FLAGS()
endif()

function(add_kc_test)
  set(options NONE)
  set(oneValueArgs NAME)
  set(multiValueArgs REQUIRES)
  cmake_parse_arguments(ADD_KC_TEST "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

  project(${ADD_KC_TEST_NAME})

  add_executable(${ADD_KC_TEST_NAME} ${ADD_KC_TEST_NAME}.cpp)

  add_test(${ADD_KC_TEST_NAME} ${ADD_KC_TEST_NAME})
  if(CODE_COVERAGE)
    SETUP_TARGET_FOR_COVERAGE_GCOVR_HTML(NAME ${ADD_KC_TEST_NAME}_COVER EXECUTABLE ${ADD_KC_TEST_NAME})
  endif()

  target_include_directories(${ADD_KC_TEST_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src .)

  message("Added KC test: " ${ADD_KC_TEST_NAME} " testing " ${ADD_KC_TEST_REQUIRES} .)

endfunction(add_kc_test)

add_kc_test(NAME TestLists REQUIRES KCLists)
# add_subdirectory(TestKCQueues) 
# add_subdirectory(TestKCStateMachine)
# add_subdirectory(TestKCBinarySearchTree)
# add_subdirectory(TestKCStacks)
