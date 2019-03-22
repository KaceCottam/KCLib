cmake_minimum_required(VERSION 3.8)

project(SimpleBSTShowcase)

set(ExSimpleBSTShowcase_FILES SimpleBSTShowcase.cpp)

include_directories(${KCBinarySearchTree_DIRECTORY})

add_executable(SimpleBSTShowcase ${ExSimpleBSTShowcase_FILES})
