#ifndef IDL_LOGGER_H
#define IDL_LOGGER_H

#include "idl_defines.h"

namespace idl {

	class IDL_API Logger {

	private:
		enum LogLevel
		{
			ERROR_LOG_LEVEL,
			WARN_LOG_LEVEL,
			INFO_LOG_LEVEL,
			DEBUG_LOG_LEVEL
		};

		static constexpr const char* LevelLogString[4] = {"[ERROR]: ", "[WARN]:  ", "[INFO]:  ", "[DEBUG]: "};
		static void log(LogLevel logLevel, const char* msm);

	public:
		static void error(const char* msm, ...);
		static void warn(const char* msm, ...);
		static void info(const char* msm, ...);
		static void debug(const char* msm, ...);
	};

#ifndef LOG_ERROR
	#define LOG_ERROR(msm, ...) idl::Logger::error(msm, ##__VA_ARGS__);
#endif

#ifndef LOG_WARN_DISABLED
	#define LOG_WARN(msm, ...) idl::Logger::warn(msm, ##__VA_ARGS__);
#else
	#define LOG_WARN(msm, ...)
#endif

#ifndef LOG_INFO_DISABLED
	#define LOG_INFO(msm, ...) idl::Logger::info(msm, ##__VA_ARGS__);
#else
	#define LOG_INFO(msm, ...)
#endif

#ifdef LOG_DEBUG_ENABLED
	#define LOG_DEBUG(msm, ...) idl::Logger::debug(msm, ##__VA_ARGS__);
#else
	#define LOG_DEBUG(msm, ...)
#endif

}  // namespace idl
#endif