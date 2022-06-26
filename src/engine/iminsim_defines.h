#ifndef IMINSIM_DEFINES_H
#define IMINSIM_DEFINES_H

// Shared library
#if defined(IMINSIM_API_SHARED_LIB_BUILD) && defined(IMINSIM_API_SHARED_LIB)
	#error "You must not have both IMINSIM_API_SHARED_LIB_BUILD and IMINSIM_API_SHARED_LIB defined"
#endif

#ifdef IMINSIM_API_SHARED_LIB_BUILD
	// Exports
	#ifdef _MSC_VER
		#define IMINSIM_API __declspec(dllexport)
	#else
		#define IMINSIM_API __attribute__((visibility("default")))
	#endif
#else
	// Imports
	#if defined(IMINSIM_API_SHARED_LIB) && defined(_MSC_VER)
		#define IMINSIM_API __declspec(dllimport)
	#else
		#define IMINSIM_API
	#endif
#endif

// Initial
#define TRUE 1
#define FALSE 0
#define NULL 0

// Unsigned int types.
typedef unsigned char u8;

// Properly define static assertions.
#if defined(__clang__) || defined(__gcc__)
	#define STATIC_ASSERT _Static_assert
#else
	#define STATIC_ASSERT static_assert
#endif

// Ensure all types are of the correct size.
STATIC_ASSERT(sizeof(u8) == 1, "Expected u8 to be 1 byte.");

#endif