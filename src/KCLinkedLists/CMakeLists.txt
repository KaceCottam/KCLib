cmake_minimum_required(VERSION 3.8)

project(KCLinkedLists VERSION 0.1)

set(KCModules ${KCModules} KCLinkedLists)
set(KCLinkedLists_FILES KCLinkedLists.hpp KCLinkedLists.cpp)
set(KCLinkedLists_HEADERS KCLinkedLists.hpp)

add_library(KCLinkedLists STATIC ${KCLinkedLists_FILES})

target_link_libraries(KCLinkedLists KCNodes)

include_directories(${KCNodes_DIRECTORY})

add_custom_command(
	TARGET KCLinkedLists POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
	${CMAKE_CURRENT_SOURCE_DIR}/KCLinkedLists.hpp
	${KCLIB_HEADER_OUTPUT_DIRECTORY}/KCLinkedLists.hpp
)
