cmake_minimum_required(VERSION 3.8)

project(TestKCStateMachine)

set(TestKCStateMachine_FILES TestStateMachine.cpp)

include_directories(
${KCStateMachine_DIRECTORY}
${Tests_DIRECTORY}
)

add_executable(TestKCStateMachine ${TestKCStateMachine_FILES})

target_link_libraries(KCStateMachine)

add_custom_command(
	TARGET TestKCStateMachine POST_BUILD
	COMMAND cmd /c ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/TestKCStateMachine.exe
)
