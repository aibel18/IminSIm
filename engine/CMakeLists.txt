# ##############################################################
# Copyright (c) 2022-present Jose Abel Ticona Larico.
# ##############################################################

# --------------------------------------------------------------
# xsim_engine library
# --------------------------------------------------------------

# headers
file(GLOB_RECURSE ENGINE_HEADERS src/*.hpp src/*.h)

# sources
file(GLOB_RECURSE ENGINE_SOURCES src/*.cpp)

# library
add_library(xsim_engine ${ENGINE_SOURCES} ${ENGINE_HEADERS})

# intern directories
target_include_directories(xsim_engine INTERFACE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/src
	$<INSTALL_INTERFACE:>/src
)

# extern libraries
add_dependencies(xsim_engine idl_platform)
target_link_libraries(xsim_engine PRIVATE idl_platform)

if(BUILD_SHARED_LIBS)
	target_compile_definitions(xsim_engine PRIVATE XSIM_API_BUILD)
	target_compile_definitions(xsim_engine PRIVATE IDL_API_SHARE)
endif()