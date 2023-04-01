# ##############################################################
# Copyright (c) 2022-present Jose Abel Ticona Larico.
# ##############################################################

# --------------------------------------------------------------
# xsim_launcher library
# --------------------------------------------------------------

# headers
file(GLOB_RECURSE LAUNCHER_HEADERS src/*.hpp src/*.h)

# sources
file(GLOB_RECURSE LAUNCHER_SOURCES src/*.cpp)

# library
add_executable(xsim_launcher ${LAUNCHER_SOURCES} ${LAUNCHER_HEADERS})

# intern directories
target_include_directories(xsim_launcher PRIVATE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/src
	$<INSTALL_INTERFACE:>/src
)

# extern libraries
target_link_libraries(xsim_launcher PRIVATE idl_platform xsim_engine)

if(BUILD_SHARED_LIBS)
	target_compile_definitions(xsim_launcher PRIVATE XSIM_API_SHARE)
	target_compile_definitions(xsim_launcher PRIVATE IDL_API_SHARE)
endif()