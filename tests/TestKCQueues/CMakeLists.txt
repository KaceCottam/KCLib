cmake_minimum_required(VERSION 3.8)

project(TestKCQueues)

set(TestKCQueues_FILES TestQueues.cpp)

include_directories(
${KCNodes_DIRECTORY}
${KCQueues_DIRECTORY}
${Tests_DIRECTORY}
)

add_executable(TestKCQueues ${TestKCQueues_FILES})

target_link_libraries(KCQueues)

add_custom_command(
	TARGET TestKCQueues POST_BUILD
	COMMAND cmd /c ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/TestKCQueues.exe
)