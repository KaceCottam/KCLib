cmake_minimum_required(VERSION 3.8)

macro(add_kc_project TARGET TARGET_VERSION)
  project(${TARGET} VERSION ${TARGET_VERSION})

  add_library(${TARGET} KCLib/${TARGET}.hpp KCLib/${TARGET}.cpp)
  set(KCModules ${KCModules} ${TARGET} PARENT_SCOPE)

  if(${ARGC} GREATER 2)
    target_include_directories(${TARGET} PRIVATE .)
    message("Added KC project: " ${TARGET} " (" ${TARGET_VERSION} ") [requires " ${ARGN} "]")
  else()
    message("Added KC project: " ${TARGET} " (" ${TARGET_VERSION} ")")
  endif() 
endmacro(add_kc_project TARGET TARGET_VERSION)

add_kc_project(KCExceptions 1.0)
add_kc_project(KCLists 2.0 KCExceptions) 
# add_kc_project(KCConsole 2.0) # UNTESTED
# add_kc_project(KCStateMachine 2.0) # UNTESTED
# add_kc_project(KCQueues 1.0) # UNTESTED
# add_kc_project(KCMusic 1.0) # UNTESTED
# add_kc_project(KCBinarySearchTree 1.0.2) # UNTESTED
# add_kc_project(KCStacks 1.0) # UNTESTED
# add_kc_project(KCCSVParser 1.0) # UNTESTED

install(TARGETS ${KCModules} 
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include)
