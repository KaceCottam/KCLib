cmake_minimum_required(VERSION 3.8)

project(KCStacks VERSION 1.0)

set(KCModules ${KCModules} KCStacks)
set(KCStacks_FILES KCStacks.hpp KCStacks.cpp)
set(KCStacks_HEADERS KCStacks.hpp)

add_library(KCStacks STATIC ${KCStacks_FILES})

set(KCLIB_FILE_COMMENT 
 " KCLIB ${PROJECT_VERSION}
// This is the KCLib ${PROJECT_NAME}. 
// Project can be found at www.github.com/KaceCottam/KCLib/")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/KCStacks.hpp ${KCLIB_HEADER_OUTPUT_DIRECTORY}/KCStacks.hpp )
