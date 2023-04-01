#ifndef XSIM_DEFINES_H
#define XSIM_DEFINES_H

// Shared library
#if defined(XSIM_API_BUILD) && defined(XSIM_API_SHARE)
	#error "You must not have both XSIM_API_BUILD and XSIM_API_SHARE defined"
#endif

#ifdef XSIM_API_BUILD
	// Exports
	#ifdef _MSC_VER
		#define XSIM_API __declspec(dllexport)
	#else
		#define XSIM_API __attribute__((visibility("default")))
	#endif
#else
	// Imports
	#if defined(XSIM_API_SHARE) && defined(_MSC_VER)
		#define XSIM_API __declspec(dllimport)
	#else
		#define XSIM_API
	#endif
#endif

// Initial
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