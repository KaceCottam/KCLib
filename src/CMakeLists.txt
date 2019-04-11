cmake_minimum_required(VERSION 3.8)

function(add_kc_project)
  set(CURRENT_OPTION "NAME")
  foreach(I IN ITEMS ${ARGN})
    if("${I}" MATCHES "NAME")
      set(CURRENT_OPTION NAME)
    elseif("${I}" MATCHES "VERSION")
      set(CURRENT_OPTION VERSION)
    elseif("${I}" MATCHES "REQUIRES")
      set(CURRENT_OPTION REQUIRES)
    elseif("${I}" MATCHES "FILES")
      set(CURRENT_OPTION FILES)
    else()
      set(${CURRENT_OPTION} ${${CURRENT_OPTION}} ${I})
    endif() 
  endforeach()

  project(${NAME} VERSION ${VERSION})

  if(${FILES})
    add_library(${NAME} KCLib/${NAME}.hpp ${FILES}})
  else()
    add_library(${NAME} KCLib/${NAME}.hpp KCLib/static.cpp)
  endif()
  set(KCModules ${KCModules} ${NAME} PARENT_SCOPE)

  set_target_properties(${NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
  )

  if(${REQUIRES})
    target_include_directories(${NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/)
    message("Added KC project: " ${NAME} " (" ${VERSION} ") [requires " ${REQUIRES} "]")
  else()
    message("Added KC project: " ${NAME} " (" ${VERSION} ")")
  endif() 
endfunction(add_kc_project)


add_kc_project(KCExceptions VERSION 1.0)
add_kc_project(KCLists VERSION 2.0 REQUIRES KCExceptions) 
add_kc_project(KCQueues VERSION 2.0 REQUIRES KCExceptions) # UNTESTED
# add_kc_project(KCConsole 2.0) # UNTESTED
# add_kc_project(KCStateMachine 2.0) # UNTESTED
# add_kc_project(KCMusic 1.0) # UNTESTED
# add_kc_project(KCBinarySearchTree 1.0.2) # UNTESTED
# add_kc_project(KCStacks 1.0) # UNTESTED
# add_kc_project(KCCSVParser 1.0) # UNTESTED

install(TARGETS ${KCModules} 
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include)
