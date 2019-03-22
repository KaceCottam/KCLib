cmake_minimum_required(VERSION 3.8)

project(KCLinkedLists VERSION 1.0)

set(KCModules ${KCModules} KCLinkedLists)
set(KCLinkedLists_FILES KCLinkedLists.hpp KCLinkedLists.cpp)
set(KCLinkedLists_HEADERS KCLinkedLists.hpp)

add_library(KCLinkedLists STATIC ${KCLinkedLists_FILES})

target_link_libraries(KCLinkedLists KCNodes)

include_directories(${KCNodes_DIRECTORY})

set(KCLIB_FILE_COMMENT 
 " KCLIB ${PROJECT_VERSION}
// This is the KCLib ${PROJECT_NAME}. 
// Project can be found at www.github.com/KaceCottam/KCLib/")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/KCLinkedLists.hpp ${KCLIB_HEADER_OUTPUT_DIRECTORY}/KCLinkedLists.hpp )
