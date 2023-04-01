# ##############################################################
# Copyright (c) 2022-present Jose Abel Ticona Larico.
# ##############################################################

# --------------------------------------------------------------
# project setup
# --------------------------------------------------------------
cmake_minimum_required(VERSION 3.1)
include(CMakeDependentOption)
project("Xsim")

# Options
option(USE_DOUBLE_PRECISION "Use double precision" OFF)
option(USE_CUDA "Use CUDA" OFF) # use cuda
option(BUILD_DEMOS "Build Demos executable" OFF)
option(GEN_DOCS "Generate documentation" OFF)
option(BUILD_SHARED_LIBS "build dinamic library" ON)

set(OUT_BUILD "/sdk")

# add common.cmake
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
include(common)

# --------------------------------------------------------------
# project structure
# --------------------------------------------------------------

# add extern libraries

# add own libraries
add_subdirectory(platform)
add_subdirectory(engine)
add_subdirectory(launcher)

# add demos
if(BUILD_DEMOS)
	add_subdirectory(demos)
	message(STATUS "build demos")
endif()