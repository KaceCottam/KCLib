cmake_minimum_required(VERSION 3.8)

project(KCMusic VERSION 0.1)

set(KCModules ${KCModules} KCMusic)
set(KCMusic_FILES KCMusic.hpp KCMusic.cpp)
set(KCMusic_HEADERS KCMusic.hpp)

add_library(KCMusic STATIC ${KCMusic_FILES})

set(KCLIB_FILE_COMMENT 
 " KCLIB ${PROJECT_VERSION}
// This is the KCLib ${PROJECT_NAME}. 
// Project can be found at www.github.com/KaceCottam/KCLib/")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/KCMusic.hpp ${KCLIB_HEADER_OUTPUT_DIRECTORY}/KCMusic.hpp )
