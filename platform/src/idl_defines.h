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

// Unsigned int types.
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

#endif