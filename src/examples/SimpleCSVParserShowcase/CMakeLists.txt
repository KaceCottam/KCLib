cmake_minimum_required(VERSION 3.8)

project(SimpleCSVParserShowcase)

set(ExSimpleCSVParserShowcase_FILES SimpleCSVParserShowcase.cpp)
set(ExSimpleCSVParserShowcase_LIBS KCCSVParser)

include_directories(${KCCSVParser_DIRECTORY})

configure_file(
	${CMAKE_CURRENT_SOURCE_DIR}/SimpleCSVParserShowcase.in.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/SimpleCSVParserShowcase.cpp
)

add_executable(SimpleCSVParserShowcase ${ExSimpleCSVParserShowcase_FILES})

target_link_libraries(SimpleCSVParserShowcase ${ExSimpleCSVParserShowcase_LIBS})
