cmake_minimum_required(VERSION 3.8)

project(SimpleConsoleShowcase)

set(ExSimpleConsoleShowcase_FILES SimpleConsoleShowcase.cpp)
set(ExSimpleConsoleShowcase_LIBS KCConsole)

include_directories(${KCConsole_DIRECTORY})

add_executable(SimpleConsoleShowcase ${ExSimpleConsoleShowcase_FILES})

target_link_libraries(SimpleConsoleShowcase ${ExSimpleConsoleShowcase_LIBS})