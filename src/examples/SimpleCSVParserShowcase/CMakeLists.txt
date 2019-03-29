cmake_minimum_required(VERSION 3.8)

project(SimpleCSVParserShowcase)

set(ExSimpleCSVParserShowcase_FILES SimpleCSVParserShowcase.cpp)
set(ExSimpleCSVParserShowcase_LIBS KCCSVParser)

include_directories(${KCCSVParser_DIRECTORY})

add_executable(SimpleCSVParserShowcase ${ExSimpleCSVParserShowcase_FILES})

target_link_libraries(SimpleCSVParserShowcase ${ExSimpleCSVParserShowcase_LIBS})

add_custom_command(
TARGET SimpleCSVParserShowcase POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy 
${CMAKE_CURRENT_SOURCE_DIR}/data.csv 
${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/data.csv)
