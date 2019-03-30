cmake_minimum_required(VERSION 3.8)

project(KCCSVParser VERSION 1.0)

set(KCModules ${KCModules} KCCSVParser)
set(KCCSVParser_FILES KCCSVParser.hpp KCCSVParser.cpp)
set(KCCSVParser_HEADERS KCCSVParser.hpp)

add_library(KCCSVParser STATIC ${KCCSVParser_FILES})

set(KCLIB_FILE_COMMENT 
 " KCLIB ${PROJECT_VERSION}
// This is the KCLib ${PROJECT_NAME}. 
// Project can be found at www.github.com/KaceCottam/KCLib/")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/KCCSVParser.hpp ${KCLIB_HEADER_OUTPUT_DIRECTORY}/KCCSVParser.hpp )
