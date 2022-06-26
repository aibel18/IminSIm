# ##############################################################
# Copyright (c) 2022-present Jose Abel Ticona Larico.
# ##############################################################

# --------------------------------------------------------------
# iminsim_engine library
# --------------------------------------------------------------

# headers
file(GLOB_RECURSE ENGINE_HEADERS ./*.hpp ./*.h)

# sources
file(GLOB_RECURSE ENGINE_SOURCES ./*.cpp)

# library
add_library(iminsim_engine ${ENGINE_SOURCES} ${ENGINE_HEADERS})

# intern directories
target_include_directories(iminsim_engine PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	$<INSTALL_INTERFACE:>
)

# extern libraries
add_dependencies(iminsim_engine idl_platform)
target_link_libraries(iminsim_engine PRIVATE idl_platform)

if(BUILD_SHARED_LIBS)
	target_compile_definitions(iminsim_engine PRIVATE IMINSIM_API_SHARED_LIB_BUILD)
	target_compile_definitions(iminsim_engine PRIVATE IDL_API_SHARED_LIB)
endif()