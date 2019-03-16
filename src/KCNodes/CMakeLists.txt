cmake_minimum_required(VERSION 3.8)

project(KCNodes VERSION 0.1)

set(KCModules ${KCModules} KCNodes)
set(KCNodes_FILES KCNodes.hpp KCNodes.cpp)
set(KCNodes_HEADERS KCNodes.hpp)

add_library(KCNodes STATIC ${KCNodes_FILES})

add_custom_command(
	TARGET KCNodes POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
	${CMAKE_CURRENT_SOURCE_DIR}/KCNodes.hpp
	${KCLIB_HEADER_OUTPUT_DIRECTORY}/KCNodes.hpp
)
