cmake_minimum_required(VERSION 3.21)
project(quill-art LANGUAGES CXX)

# Enforce Ninja as the generator.
if(NOT CMAKE_GENERATOR STREQUAL "Ninja")
    message(FATAL_ERROR "This project requires Ninja as the generator.")
endif()

# Set default build type to Debug if not specified.
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose Debug or Release" FORCE)
endif()

# Select the appropriate toolchain (if TARGET_OS is defined).
if(DEFINED TARGET_OS)
    if(TARGET_OS STREQUAL "Linux")
        set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/toolchains/linux.cmake)
    elseif(TARGET_OS STREQUAL "Windows")
        set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/toolchains/windows.cmake)
    elseif(TARGET_OS STREQUAL "MacOS")
        set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/toolchains/macos.cmake)
    else()
        message(FATAL_ERROR "Unsupported TARGET_OS: ${TARGET_OS}")
    endif()
endif()

# Enforce Clang.
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

# Enable C++23 standard.
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Glob all source files in the src directory (this will include your app, renderer, UI, SVG, tools, etc.).
file(GLOB_RECURSE SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)

# Glob ImGui core source files from lib/IMGUI.
file(GLOB IMGUI_SOURCES
    ${CMAKE_SOURCE_DIR}/lib/IMGUI/imgui.cpp
    ${CMAKE_SOURCE_DIR}/lib/IMGUI/imgui_draw.cpp
    ${CMAKE_SOURCE_DIR}/lib/IMGUI/imgui_widgets.cpp
    ${CMAKE_SOURCE_DIR}/lib/IMGUI/imgui_tables.cpp
    ${CMAKE_SOURCE_DIR}/lib/IMGUI/imgui_demo.cpp
)

# Glob ImGui backend source files for GLFW and OpenGL3.
file(GLOB IMGUI_BACKEND
    ${CMAKE_SOURCE_DIR}/lib/IMGUI/imgui_impl_glfw.cpp
    ${CMAKE_SOURCE_DIR}/lib/IMGUI/imgui_impl_opengl3.cpp
)

# Combine all sources (your project sources and ImGui sources) into one list.
set(ALL_SOURCES ${SRC_FILES} ${IMGUI_SOURCES} ${IMGUI_BACKEND})

# Compile the executable using the combined source list.
add_executable(quill-art ${ALL_SOURCES})

# Include headers from the lib directory (including IMGUI headers) and the include directory.
target_include_directories(quill-art PRIVATE
    ${CMAKE_SOURCE_DIR}/lib
    ${CMAKE_SOURCE_DIR}/include
)

# Set compiler build flags.
target_compile_options(quill-art PRIVATE -Wall -Wextra -pedantic)
