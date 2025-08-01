cmake_minimum_required(VERSION 3.10)
project(OpenDAW)

# Requires C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)

endif()

# Include the GTK headers and libraries
include_directories(${GTK4_INCLUDE_DIRS})
link_directories(${GTK4_LIBRARY_DIRS})

add_definitions(${GTK4_CFLAGS_OTHER})

set(SOURCES
    main.cpp
    DawUI.cpp
    AudioError.c 
    AudioCore.c 
    Common.c
)

add_executable(${PROJECT_NAME} ${SOURCES})