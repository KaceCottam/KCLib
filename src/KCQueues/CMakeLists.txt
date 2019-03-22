cmake_minimum_required(VERSION 3.8)

project(KCQueues VERSION 1.0)

set(KCModules ${KCModules} KCQueues)
set(KCQueues_FILES KCQueues.hpp KCQueues.cpp)
set(KCQueues_HEADERS KCQueues.hpp)

add_library(KCQueues STATIC ${KCQueues_FILES})

target_link_libraries(KCQueues KCNodes)

include_directories(${KCNodes_DIRECTORY})

set(KCLIB_FILE_COMMENT 
 " KCLIB ${PROJECT_VERSION}
// This is the KCLib ${PROJECT_NAME}. 
// Project can be found at www.github.com/KaceCottam/KCLib/")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/KCQueues.hpp ${KCLIB_HEADER_OUTPUT_DIRECTORY}/KCQueues.hpp )
