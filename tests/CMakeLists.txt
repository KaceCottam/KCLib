cmake_minimum_required(VERSION 3.8)

include(CTest)

function(add_kc_test)
  set(options NONE)
  set(oneValueArgs NAME TARGET)
  set(multiValueArgs REQUIRES)
  cmake_parse_arguments(ADD_KC_TEST "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

  project(${ADD_KC_TEST_NAME})

  add_executable(${ADD_KC_TEST_NAME} ${ADD_KC_TEST_NAME}.cpp)

  add_test(${ADD_KC_TEST_NAME} ${ADD_KC_TEST_NAME})
  if(CODE_COVERAGE)
    setup_target_for_coverage_gcovr_html(NAME ${ADD_KC_TEST_NAME}_COVER 
    EXECUTABLE ${ADD_KC_TEST_TARGET} 
    DEPENDENCIES ${ADD_KC_TEST_NAME} ${ADD_KC_TEST_REQUIRES})
  endif()

  target_include_directories(${ADD_KC_TEST_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src .)

  message("Added KC test: " ${ADD_KC_TEST_NAME} " testing " ${ADD_KC_TEST_REQUIRES} .)

endfunction(add_kc_test)

add_kc_test(NAME TestLists TARGET ctest REQUIRES KCLists)
# add_subdirectory(TestKCQueues) 
# add_subdirectory(TestKCStateMachine)
# add_subdirectory(TestKCBinarySearchTree)
# add_subdirectory(TestKCStacks)
