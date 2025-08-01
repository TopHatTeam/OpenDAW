cmake_minimum_required(VERSION 3.10)
project(OpenDAW)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GTK4 REQUIRED gtk4)
endif()

add_executable(${PROJECT_NAME}
    main.cpp
    DawUI.cpp
    AudioError.c
    AudioCore.c
    Common.c
)

target_include_directories(${PROJECT_NAME} PRIVATE ${GTK4_INCLUDE_DIRS})
target_compile_options(${PROJECT_NAME} PRIVATE ${GTK4_CFLAGS_OTHER})
target_link_libraries(${PROJECT_NAME} PRIVATE ${GTK4_LIBRARIES})

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE ole32 uuid dsound)
endif()
