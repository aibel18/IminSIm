#ifndef XSIM_LOGGER_H
#define XSIM_LOGGER_H

#include "defines.h"

namespace xsim {

	class XSIM_API Logger {

	private:
		enum LogLevel
		{
			ERROR_LOG_LEVEL,
			WARN_LOG_LEVEL,
			INFO_LOG_LEVEL,
			DEBUG_LOG_LEVEL
		};

	public:
		static void error(const char* msm, ...);
		static void warn(const char* msm, ...);
		static void info(const char* msm, ...);
		static void debug(const char* msm, ...);
	};

#ifndef LOG_ERROR
	#define LOG_ERROR(msm, ...) xsim::Logger::error(msm, ##__VA_ARGS__);
#endif

#ifndef LOG_WARN_DISABLED
	#define LOG_WARN(msm, ...) xsim::Logger::warn(msm, ##__VA_ARGS__);
#else
	#define LOG_WARN(msm, ...)
#endif

#ifndef LOG_INFO_DISABLED
	#define LOG_INFO(msm, ...) xsim::Logger::info(msm, ##__VA_ARGS__);
#else
	#define LOG_INFO(msm, ...)
#endif

#ifdef LOG_DEBUG_ENABLED
	#define LOG_DEBUG(msm, ...) xsim::Logger::debug(msm, ##__VA_ARGS__);
#else
	#define LOG_DEBUG(msm, ...)
#endif

}  // namespace xsim
#endif