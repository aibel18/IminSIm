#ifndef XSIM_LOGGER_H
#define XSIM_LOGGER_H

#include "defines.h"
#include <sstream>

namespace xsim {

	enum LogLevel
	{
		ERROR = 0,
		WARN,
		INFO,
		DEBUG
	};

	class XSIM_API Logger {

	private:
		std::ostringstream message;
		LogLevel level;

	public:
		Logger(LogLevel logLevel = LogLevel::INFO);
		~Logger();

		template <typename T>
		Logger& operator<<(const T& value);
	};

	template <typename T>
	inline Logger& Logger::operator<<(const T& value) {
		message << value;
		return *this;
	};

#define LOG_ERROR xsim::Logger(LogLevel::ERROR)
#define LOG_WARN xsim::Logger(LogLevel::WARN)
#define LOG_INFO xsim::Logger(LogLevel::INFO)
#ifdef LOG_DEBUG_ENABLED
	#define LOG_DEBUG xsim::Logger(LogLevel::DEBUG)
#else
	#define LOG_DEBUG / ## /
#endif

}  // namespace xsim
#endif