cmake_minimum_required(VERSION 3.8)

macro(add_kc_project TARGET TARGET_VERSION)
  project(${TARGET} VERSION ${TARGET_VERSION})
  set(KCModules ${KCModules} ${TARGET} PARENT_SCOPE)
  add_library(${TARGET} ${TARGET}/${TARGET}.hpp ${TARGET}/${TARGET}.cpp ${ARGN})
  message("Added KC project: " ${TARGET} " (" ${TARGET_VERSION} ")")
endmacro(add_kc_project TARGET TARGET_VERSION)

add_kc_project(KCConsole 2.0) 
add_kc_project(KCStateMachine 2.0) 
add_kc_project(KCNodes 1.0) 
add_kc_project(KCLinkedLists 1.0) 
add_kc_project(KCQueues 1.0) 
add_kc_project(KCMusic 1.0)
add_kc_project(KCBinarySearchTree 1.0.2)
add_kc_project(KCStacks 1.0)
add_kc_project(KCCSVParser 1.0)

install(TARGETS ${KCModules} 
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include)
