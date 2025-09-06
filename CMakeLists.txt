cmake_minimum_required(VERSION 3.10)
if(WIN32)
    project(OpenDAW LANGUAGES C CXX)
endif()

if (UNIX AND NOT APPLE)
    project(OpenDAW LANGUAGES C CXX)
endif()

if(APPLE)
    project(OpenDAW LANGUAGES C CXX OBJCXX)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# -----------------------------
# External dependencies (from extern/)
# -----------------------------
add_subdirectory(extern/rtmidi)     # midi library
add_subdirectory(extern/fmt)        # fmt
add_subdirectory(extern/libsndfile) # sound library
add_subdirectory(extern/SDL)        # SDL3
add_subdirectory(extern/ImGuiFileDialog)

# -----------------------------
# Vulkan (system package)
# -----------------------------
find_package(Vulkan REQUIRED)

# -----------------------------
# Dear ImGui (SDL3 + Vulkan backends)
# -----------------------------
add_library(imgui STATIC 
    extern/imgui/imgui.cpp
    extern/imgui/imgui_draw.cpp
    extern/imgui/imgui_tables.cpp
    extern/imgui/imgui_widgets.cpp

    # backends for SDL3 + Vulkan
    extern/imgui/backends/imgui_impl_sdl3.cpp
    extern/imgui/backends/imgui_impl_vulkan.cpp
)

target_include_directories(imgui PUBLIC 
    extern/imgui
    extern/imgui/backends
)

target_include_directories(ImGuiFileDialog PUBLIC
    extern/ImGuiFileDialog
    extern/imgui 
    extern/imgui/backends
)

target_link_libraries(imgui PUBLIC
    SDL3::SDL3
    Vulkan::Vulkan
)

# fuck rust

# -----------------------------
# OpenDAW library
# -----------------------------
#add_subdirectory(OpenDAWLib)

# -----------------------------
# Executable for specific platforms
# -----------------------------
if(WIN32)
    add_executable(${PROJECT_NAME}
        main.cpp
        Midi.cpp
        AudioError.c
        AudioCore.c
        Common.c
        gui.cpp
        vst.c   # VST support
        projectfile.c
    )
endif()

if(UNIX AND NOT APPLE)
    add_executable(${PROJECT_NAME}
        main.cpp
        Midi.cpp
        AudioError.c
        AudioCore.c
        Common.c
        gui.cpp
        vst.c   # VST support
        projectfile.c
    )
endif()

if(APPLE)
    add_executable(${PROJECT_NAME}
        main.cpp
        Midi.cpp
        apple_platform.mm
        AudioError.c
        AudioCore.c
        Common.c
        gui.cpp
        vst.c   # VST support
        projectfile.c
    )
endif()


# -----------------------------
# Qt6 (required)
# -----------------------------
#find_package(Qt6 REQUIRED COMPONENTS Widgets)

# -----------------------------
# Link everything
# -----------------------------
target_link_libraries(${PROJECT_NAME} PRIVATE
    #OpenDAWLibStatic
    rtmidi
    SndFile::sndfile
    fmt::fmt
    SDL3::SDL3
    Vulkan::Vulkan
    imgui
    ImGuiFileDialog
)

# -----------------------------
# Platform-specific bits
# -----------------------------
if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE ole32 uuid dsound)
endif()

if(UNIX AND NOT APPLE)
    find_package(ALSA REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE asound)
endif()
