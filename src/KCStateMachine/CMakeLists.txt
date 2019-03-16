cmake_minimum_required(VERSION 3.8)

project(KCStateMachine VERSION 0.1)

set(KCModules ${KCModules} KCStateMachine)
set(KCStateMachine_FILES KCStateMachine.hpp KCStateMachine.cpp)
set(KCStateMachine_HEADERS KCStateMachine.hpp)

add_library(KCStateMachine STATIC ${KCStateMachine_FILES})

add_custom_command(
	TARGET KCStateMachine POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
	${CMAKE_CURRENT_SOURCE_DIR}/KCStateMachine.hpp
	${KCLIB_HEADER_OUTPUT_DIRECTORY}/KCStateMachine.hpp
)
