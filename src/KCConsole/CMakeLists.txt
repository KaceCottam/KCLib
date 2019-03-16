cmake_minimum_required(VERSION 3.8)

project(KCConsole VERSION 0.1)

set(KCModules ${KCModules} KCConsole)
set(KCConsole_FILES KCConsole.hpp KCConsole.cpp)
set(KCConsole_HEADERS KCConsole.hpp)

add_library(KCConsole STATIC ${KCConsole_FILES})

add_custom_command(
	TARGET KCConsole POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
	${CMAKE_CURRENT_SOURCE_DIR}/KCConsole.hpp
	${KCLIB_HEADER_OUTPUT_DIRECTORY}/KCConsole.hpp
)
