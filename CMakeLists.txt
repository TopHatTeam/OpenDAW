cmake_minimum_required(VERSION 3.10)
project(OpenDAW)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Add executable first
add_executable(${PROJECT_NAME}
    main.cpp
    DawUI.cpp
    AudioError.c
    AudioCore.c
    Common.c
)

# Find Qt6 after defining the executable
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Link Qt6 Widgets
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)

# Windows-specific libraries
if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE ole32 uuid dsound)
endif()

# GTK4 for UNIX (optional, if you still want it)
if(UNIX)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GTK4 REQUIRED gtk4)
    # Uncomment if you need GTK4
    # target_include_directories(${PROJECT_NAME} PRIVATE ${GTK4_INCLUDE_DIRS})
    # target_compile_options(${PROJECT_NAME} PRIVATE ${GTK4_CFLAGS_OTHER})
    # target_link_libraries(${PROJECT_NAME} PRIVATE ${GTK4_LIBRARIES})
endif()
