cmake_minimum_required(VERSION 3.8)

project(KCStateMachine VERSION 2.0)

set(KCModules ${KCModules} KCStateMachine)
set(KCStateMachine_FILES KCStateMachine.hpp KCStateMachine.cpp)
set(KCStateMachine_HEADERS KCStateMachine.hpp)

add_library(KCStateMachine STATIC ${KCStateMachine_FILES})

set(KCLIB_FILE_COMMENT 
 " KCLIB ${PROJECT_VERSION}
// This is the KCLib ${PROJECT_NAME}. 
// Project can be found at www.github.com/KaceCottam/KCLib/")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/KCStateMachine.hpp ${KCLIB_HEADER_OUTPUT_DIRECTORY}/KCStateMachine.hpp )
