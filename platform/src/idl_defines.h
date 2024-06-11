#ifndef IDL_DEFINES_H
#define IDL_DEFINES_H

// Platform detection
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
	#define IDL_WINDOWS_PLATFORM 1
	#ifndef _WIN64
		#error "64-bit is required on Windows!"
	#endif
#elif defined(__linux__) || defined(__gnu_linux__)
	// Linux OS
	#define IDL_LINUX_PLATFORM 1
	#if defined(__ANDROID__)
		#define IDL_ANDROID_PLATFORM 1
	#endif
#elif defined(__unix__)
	// Catch anything not caught by the above.
	#define IDL_UNIX_PLATFORM 1
#elif defined(_POSIX_VERSION)
	// Posix
	#define IDL_POSIX_PLATFORM 1
#elif __APPLE__
	// Apple platforms
	#define IDL_APPLE_PLATFORM 1
	#include <TargetConditionals.h>
	#if TARGET_IPHONE_SIMULATOR
		// iOS Simulator
		#define IDL_IOS_PLATFORM 1
		#define IDL_IOS_SIMULATOR_PLATFORM 1
	#elif TARGET_OS_IPHONE
		#define IDL_IOS_PLATFORM 1
	// iOS device
	#elif TARGET_OS_MAC
	// Other kinds of Mac OS
	#else
		#error "Unknown Apple platform"
	#endif
#else
	#error "Unknown platform!"
#endif

// Shared library
#if defined(IDL_API_BUILD) && defined(IDL_API_SHARE)
	#error "You must not have both IDL_API_BUILD and IDL_API_SHARE defined"
#endif

#ifdef IDL_API_BUILD
	// Exports
	#ifdef _MSC_VER
		#define IDL_API __declspec(dllexport)
	#else
		#define IDL_API __attribute__((visibility("default")))
	#endif
#else
	// Imports
	#if defined(IDL_API_SHARE) && defined(_MSC_VER)
		#define IDL_API __declspec(dllimport)
	#else
		#define IDL_API
	#endif
#endif

// Properly define static assertions.
#if defined(__clang__) || defined(__gcc__)
	#define STATIC_ASSERT _Static_assert
#else
	#define STATIC_ASSERT static_assert
#endif

// Initial
#ifndef NULL
    #define NULL 0
#endif

// TODO: separate this block in numeric defines
// Unsigned int types.

// Unsigned 8-bit integer.
typedef unsigned char u8;
// Unsigned 16-bit integer.
typedef unsigned short u16;
// Unsigned 32-bit integer.
typedef unsigned int u32;
// Unsigned 64-bit integer.
typedef unsigned long long u64;

// Signed int types.

// Unsigned 8-bit integer.
typedef signed char i8;
// Unsigned 16-bit integer.
typedef signed short i16;
// Unsigned 32-bit integer.
typedef signed int i32;
// Unsigned 64-bit integer.
typedef signed long long i64;

// Floating point types.

// 32-bit floating point number.
typedef float f32;
// 64-bit floating point number.
typedef double f64;
// 128-bit floating point number.
typedef long double f148; // TODO: change the nomenclature to f4, f8, f16 floating point types

// Ensure all types are of the correct size.
STATIC_ASSERT(sizeof(u8) == 1, "Expected u8 to be 1 byte.");
STATIC_ASSERT(sizeof(u16) == 2, "Expected u16 to be 2 bytes.");
STATIC_ASSERT(sizeof(u32) == 4, "Expected u32 to be 4 bytes.");
STATIC_ASSERT(sizeof(u64) == 8, "Expected u64 to be 8 bytes.");

STATIC_ASSERT(sizeof(i8) == 1, "Expected i8 to be 1 bytes.");
STATIC_ASSERT(sizeof(i16) == 2, "Expected i16 to be 2 bytes.");
STATIC_ASSERT(sizeof(i32) == 4, "Expected i32 to be 4 bytes.");
STATIC_ASSERT(sizeof(i64) == 8, "Expected i64 to be 8 bytes.");

STATIC_ASSERT(sizeof(f32) == 4, "Expected u32 to be 4 bytes.");
STATIC_ASSERT(sizeof(f64) == 8, "Expected u64 to be 8 bytes.");
STATIC_ASSERT(sizeof(f148) >= 16, "Expected u64 to be 16 bytes.");

#endif