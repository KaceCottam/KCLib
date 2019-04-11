cmake_minimum_required(VERSION 3.8)

enable_testing()

function(add_kc_test)
  set(CURRENT_OPTION NAME)
  foreach(I IN ITEMS ${ARGN})
    if("${I}" MATCHES "NAME")
      set(CURRENT_OPTION NAME)
    elseif("${I}" MATCHES "REQUIRES")
      set(CURRENT_OPTION REQUIRES)
    else()
      set(${CURRENT_OPTION} ${${CURRENT_OPTION}} ${I})
    endif() 
  endforeach()
  

  project(${NAME})

  add_executable(${NAME} ${NAME}.cpp)

  add_test(${NAME} ${NAME})

  target_include_directories(${NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src .)

  message("Added KC test: " ${NAME} " testing " ${REQUIRES} .)

endfunction(add_kc_test)

add_kc_test(TestLists REQUIRES KCLists)
# add_subdirectory(TestKCQueues) 
# add_subdirectory(TestKCStateMachine)
# add_subdirectory(TestKCBinarySearchTree)
# add_subdirectory(TestKCStacks)
