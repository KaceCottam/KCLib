cmake_minimum_required(VERSION 3.8)

project(TestKCBinarySearchTree)

set(TestKCBinarySearchTree_FILES TestBinarySearchTree.cpp)

include_directories(
${KCBinarySearchTree_DIRECTORY}
${Tests_DIRECTORY}
)

add_executable(TestKCBinarySearchTree ${TestKCBinarySearchTree_FILES})

add_custom_command(
	TARGET TestKCBinarySearchTree POST_BUILD
	COMMAND cmd /c ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/TestKCBinarySearchTree.exe
)