cmake_minimum_required(VERSION 3.8)

project(KCBinarySearchTree VERSION 0.1)

set(KCModules ${KCModules} KCBinarySearchTree)
set(KCBinarySearchTree_FILES KCBinarySearchTree.hpp KCBinarySearchTree.cpp)
set(KCBinarySearchTree_HEADERS KCBinarySearchTree.hpp)

add_library(KCBinarySearchTree STATIC ${KCBinarySearchTree_FILES})

set(KCLIB_FILE_COMMENT 
 " KCLIB ${PROJECT_VERSION}
// This is the KCLib ${PROJECT_NAME}. 
// Project can be found at www.github.com/KaceCottam/KCLib/")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/KCBinarySearchTree.hpp ${KCLIB_HEADER_OUTPUT_DIRECTORY}/KCBinarySearchTree.hpp )
