# Proprietary & Confidential — All Rights Reserved — Copyright (c) 2026 Bohdan Lysychenko — See LICENSE.

cmake_minimum_required(VERSION 3.20)

project(BTest LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CTest)
include(${CMAKE_SOURCE_DIR}/CMakeHelper.cmake)

# Required for IDE and clang linters
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Clang-Tidy integration
find_program(CLANG_TIDY_EXE NAMES clang-tidy)
if (CLANG_TIDY_EXE)
    set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}")
endif ()

# Add subdirectories for different components
add_subdirectory(BTest)
