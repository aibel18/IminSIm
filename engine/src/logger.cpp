#include "logger.h"
#include <log.h>
#include <stdarg.h> /* va_list, va_start, va_arg, va_end */
#include <string>

const char* LevelLogString[4] = {"[ERROR]: ", "[WARN]:  ", "[INFO]:  ", "[DEBUG]: "};

void xsim::Logger::error(const char* msm, ...) {
	char buffer[2048];
	va_list args;

	va_start(args, msm);
	vsnprintf(buffer, 2048, msm, args);
	va_end(args);

	std::string s = LevelLogString[ERROR_LOG_LEVEL];
	s.append(buffer);
	idl::console_write(s.c_str());
}

void xsim::Logger::warn(const char* msm, ...) {
	char buffer[2048];
	va_list args;

	va_start(args, msm);
	vsnprintf(buffer, 2048, msm, args);
	va_end(args);

	std::string s = LevelLogString[WARN_LOG_LEVEL];
	s.append(buffer);
	idl::console_write(s.c_str());
}

void xsim::Logger::info(const char* msm, ...) {
	char buffer[2048];
	va_list args;

	va_start(args, msm);
	vsnprintf(buffer, 2048, msm, args);
	va_end(args);

	std::string s = LevelLogString[INFO_LOG_LEVEL];
	s.append(buffer);
	idl::console_write(s.c_str());
}

void xsim::Logger::debug(const char* msm, ...) {
	char buffer[2048];
	va_list args;

	va_start(args, msm);
	vsnprintf(buffer, 2048, msm, args);
	va_end(args);

	std::string s = LevelLogString[DEBUG_LOG_LEVEL];
	s.append(buffer);
	idl::console_write(s.c_str());
}