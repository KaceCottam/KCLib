cmake_minimum_required(VERSION 3.8)

project(KCNodes VERSION 1.0)

set(KCModules ${KCModules} KCNodes)
set(KCNodes_FILES KCNodes.hpp KCNodes.cpp)
set(KCNodes_HEADERS KCNodes.hpp)

add_library(KCNodes STATIC ${KCNodes_FILES})

set(KCLIB_FILE_COMMENT 
 " KCLIB ${PROJECT_VERSION}
// This is the KCLib ${PROJECT_NAME}. 
// Project can be found at www.github.com/KaceCottam/KCLib/")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/KCNodes.hpp ${KCLIB_HEADER_OUTPUT_DIRECTORY}/KCNodes.hpp )
