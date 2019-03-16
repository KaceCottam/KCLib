# Install script for directory: C:/dev/KCLibCMake/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Users/kacea/CMakeBuilds/baade8bd-1ee7-5e32-a0ba-dab10e35b819/install/x86-Debug")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/dev/KCLibCMake/build/x86-Debug/src/KCConsole/cmake_install.cmake")
  include("C:/dev/KCLibCMake/build/x86-Debug/src/KCStateMachine/cmake_install.cmake")
  include("C:/dev/KCLibCMake/build/x86-Debug/src/KCNodes/cmake_install.cmake")
  include("C:/dev/KCLibCMake/build/x86-Debug/src/KCLinkedLists/cmake_install.cmake")
  include("C:/dev/KCLibCMake/build/x86-Debug/src/KCQueues/cmake_install.cmake")
  include("C:/dev/KCLibCMake/build/x86-Debug/src/examples/cmake_install.cmake")

endif()

