cmake_minimum_required(VERSION 3.8)

project(KCMusic VERSION 0.1)

set(KCModules ${KCModules} KCMusic)
set(KCMusic_FILES KCMusic.hpp KCMusic.cpp)
set(KCMusic_HEADERS KCMusic.hpp)

add_library(KCMusic STATIC ${KCMusic_FILES})

target_link_libraries(KCMusic KCNodes)

include_directories(${KCNodes_DIRECTORY})

add_custom_command(
	TARGET KCMusic POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
	${CMAKE_CURRENT_SOURCE_DIR}/KCMusic.hpp
	${KCLIB_HEADER_OUTPUT_DIRECTORY}/KCMusic.hpp
)
