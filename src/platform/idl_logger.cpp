#include "idl_logger.h"
#include <iostream>
#include <stdarg.h> /* va_list, va_start, va_arg, va_end */

inline void idl::Logger::log(LogLevel logLevel, const char* msm) {
	std::cout << LevelLogString[logLevel] << msm << std::endl;
}

inline void idl::Logger::error(const char* msm, ...) {
	char buffer[2048];
	va_list args;

	va_start(args, msm);
	vsnprintf(buffer, 2048, msm, args);
	va_end(args);

	log(ERROR_LOG_LEVEL, buffer);
}

inline void idl::Logger::warn(const char* msm, ...) {
	char buffer[2048];
	va_list args;

	va_start(args, msm);
	vsnprintf(buffer, 2048, msm, args);
	va_end(args);

	log(WARN_LOG_LEVEL, buffer);
}

inline void idl::Logger::info(const char* msm, ...) {
	char buffer[2048];
	va_list args;

	va_start(args, msm);
	vsnprintf(buffer, 2048, msm, args);
	va_end(args);

	log(INFO_LOG_LEVEL, buffer);
}

inline void idl::Logger::debug(const char* msm, ...) {
	char buffer[2048];
	va_list args;

	va_start(args, msm);
	vsnprintf(buffer, 2048, msm, args);
	va_end(args);

	log(DEBUG_LOG_LEVEL, buffer);
}