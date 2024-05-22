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

#endif