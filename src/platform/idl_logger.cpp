#include "idl_logger.h"
#include <iostream>
#include <stdarg.h> /* va_list, va_start, va_arg, va_end */

inline void idl::Logger::log(const char* logLevel, const char* msm) {	
	std::cout << logLevel << msm << std::endl;
}

void idl::Logger::error(const char* msm, ...) {
	char buffer[2048];
	va_list args;

	va_start(args, msm);
	vsnprintf(buffer, 2048, msm, args);
	va_end(args);

	log(LevelLogString[ERROR_LOG_LEVEL], buffer);
}

void idl::Logger::warn(const char* msm, ...) {
	char buffer[2048];
	va_list args;

	va_start(args, msm);
	vsnprintf(buffer, 2048, msm, args);
	va_end(args);

	log(LevelLogString[WARN_LOG_LEVEL], buffer);
}

void idl::Logger::info(const char* msm, ...) {
	char buffer[2048];
	va_list args;

	va_start(args, msm);
	vsnprintf(buffer, 2048, msm, args);
	va_end(args);

	log(LevelLogString[INFO_LOG_LEVEL], buffer);
}

void idl::Logger::debug(const char* msm, ...) {
	char buffer[2048];
	va_list args;

	va_start(args, msm);
	vsnprintf(buffer, 2048, msm, args);
	va_end(args);

	log(LevelLogString[DEBUG_LOG_LEVEL], buffer);
}