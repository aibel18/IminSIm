#include "logger.h"
#include <idl_log.h>

const char* LevelLogString[4] = {"[ERROR]: ", "[WARN ]: ", "[INFO ]: ", "[DEBUG]: "};

xsim::Logger::Logger(LogLevel logLevel) : level(logLevel) {
	message << LevelLogString[logLevel];
}

xsim::Logger::~Logger() {
	auto msg = message.str();
	idl::console_write(msg.c_str(), msg.size(), level);
}