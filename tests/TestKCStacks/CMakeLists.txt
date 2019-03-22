cmake_minimum_required(VERSION 3.8)

project(TestKCStacks)

set(TestKCStacks_FILES TestStacks.cpp)

include_directories(
${KCStacks_DIRECTORY}
${Tests_DIRECTORY}
)

add_executable(TestKCStacks ${TestKCStacks_FILES})

target_link_libraries(KCStacks)

add_custom_command(
	TARGET TestKCStacks POST_BUILD
	COMMAND cmd /c ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/TestKCStacks.exe
)
