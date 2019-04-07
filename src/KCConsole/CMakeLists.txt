cmake_minimum_required(VERSION 3.8)

project(KCConsole VERSION 2.0)

set(KCModules ${KCModules} KCConsole)
set(KCConsole_FILES KCConsole.hpp KCConsole.cpp)
set(KCConsole_HEADERS KCConsole.hpp)

add_library(KCConsole STATIC ${KCConsole_FILES})

set(KCLIB_FILE_COMMENT 
 " KCLIB ${PROJECT_VERSION}
// This is the KCLib ${PROJECT_NAME}. 
// Project can be found at www.github.com/KaceCottam/KCLib/")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/KCConsole.hpp ${KCLIB_HEADER_OUTPUT_DIRECTORY}/KCConsole.hpp )
