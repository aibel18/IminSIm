#ifndef XSIM_LOGGER_H
#define XSIM_LOGGER_H

#include "defines.h"
#include <string.h>
#include <stdio.h>
#include <idl_log.h>

namespace xsim {

#define N 256

	extern XSIM_API const char *LogLevelString[4];
	enum LogLevel { ERROR = 0, WARN, INFO, DEBUG };

	// TODO: improve log
	class XSIM_API Logger {

	public:
		Logger();

		void write(LogLevel level, const char *line, int size);

		template <typename... Args>
		inline void log(LogLevel level, const char *format, const Args &...args) {

			char line[N] = "%s";
			strcat_s(line, format);

			char buffer[N];
			int size = idl::Format(buffer, N, line, LogLevelString[level], args...);

			write(level, buffer, size);
		}
	};

	extern XSIM_API Logger logger;

#define LOG_ERROR(msm, ...) xsim::logger.log(xsim::LogLevel::ERROR, msm, ##__VA_ARGS__)
#define LOG_WARN(msm, ...)  xsim::logger.log(xsim::LogLevel::WARN, msm, ##__VA_ARGS__)
#define LOG_INFO(msm, ...)  xsim::logger.log(xsim::LogLevel::INFO, msm, ##__VA_ARGS__)
#ifdef LOG_DEBUG_ENABLED
	#define LOG_DEBUG(msm, ...) xsim::logger.log(xsim::LogLevel::DEBUG, msm, ##__VA_ARGS__)
#else
	#define LOG_DEBUG(msm, ...)
#endif

}  // namespace xsim
#endif