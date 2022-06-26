# ##############################################################
# Copyright (c) 2022-present Jose Abel Ticona Larico.
# ##############################################################

# --------------------------------------------------------------
# iminsim_launcher library
# --------------------------------------------------------------

# headers
file(GLOB_RECURSE LAUNCHER_HEADERS ./*.hpp ./*.h)

# sources
file(GLOB_RECURSE LAUNCHER_SOURCES ./*.cpp)

# library
add_executable(iminsim_launcher ${LAUNCHER_SOURCES} ${LAUNCHER_HEADERS})

# intern directories
# target_include_directories(iminsim_launcher INTERFACE
# 	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
# 	$<INSTALL_INTERFACE:>
# )

# extern libraries
add_dependencies(iminsim_launcher idl_platform iminsim_engine)
target_link_libraries(iminsim_launcher PRIVATE idl_platform iminsim_engine)

if(BUILD_SHARED_LIBS)
	target_compile_definitions(iminsim_launcher PRIVATE IMINSIM_API_SHARED_LIB)
	target_compile_definitions(iminsim_launcher PRIVATE IDL_API_SHARED_LIB)
endif()