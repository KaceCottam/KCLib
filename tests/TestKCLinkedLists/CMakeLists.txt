cmake_minimum_required(VERSION 3.8)

project(TestKCLinkedLists)

set(TestKCLinkedLists_FILES TestLinkedLists.cpp)

include_directories(
${KCNodes_DIRECTORY}
${KCLinkedLists_DIRECTORY}
${Tests_DIRECTORY}
)

add_executable(TestKCLinkedLists ${TestKCLinkedLists_FILES})

target_link_libraries(KCLinkedLists)

add_custom_command(
	TARGET TestKCLinkedLists POST_BUILD
	COMMAND cmd /c ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/TestKCLinkedLists.exe
)