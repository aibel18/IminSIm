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

if(WIN32)
	list(APPEND PLATFORM_LIBS "-luser32")
	message(STATUS "Using Win32 for window creation")
elseif(UNIX)
	list(APPEND PLATFORM_LIBS "-lX11")
	message(STATUS "Using X11 for window creation")
else()
	message(FATAL_ERROR "No supported platform was detected")
endif()

# headers
file(GLOB_RECURSE PLATFORM_HEADERS src/*.hpp src/*.h)

# sources
file(GLOB_RECURSE PLATFORM_SOURCES src/*.cpp)

# library
add_library(idl_platform ${PLATFORM_SOURCES} ${PLATFORM_HEADERS})

# intern directories
target_include_directories(idl_platform PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/src
	$<INSTALL_INTERFACE:>/src
)

# extern directories
target_include_directories(idl_platform
	PRIVATE ${PLATFORM_INCLUDES}
)

# extern libraries
target_link_libraries(idl_platform PRIVATE ${PLATFORM_LIBS})

if(BUILD_SHARED_LIBS)
	target_compile_definitions(idl_platform PRIVATE IDL_API_BUILD)
endif()