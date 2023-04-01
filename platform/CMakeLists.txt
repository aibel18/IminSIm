# ##############################################################
# Copyright (c) 2022-present Jose Abel Ticona Larico.
# ##############################################################

# --------------------------------------------------------------
# idl_platform library
# --------------------------------------------------------------

# includes
set(PLATFORM_INCLUDES)

# lib
set(PLATFORM_LIBS)

# headers
file(GLOB_RECURSE PLATFORM_HEADERS src/*.hpp src/*.h)

# sources
file(GLOB_RECURSE PLATFORM_SOURCES src/*.cpp)

# library
add_library(idl_platform ${PLATFORM_SOURCES} ${PLATFORM_HEADERS})

# intern directories
target_include_directories(idl_platform INTERFACE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/src
	$<INSTALL_INTERFACE:>/src
)

# extern directories
target_include_directories(idl_platform
	PUBLIC ${PLATFORM_INCLUDES}
)

# extern libraries
# target_link_libraries(idl_platform PUBLIC ${PLATFORM_LIBS})

if(BUILD_SHARED_LIBS)
	target_compile_definitions(idl_platform PRIVATE IDL_API_BUILD)
endif()