#include "logger.h"
#include <idl_log.h>

const char* LevelLogString[4] = {"[ERROR]: ", "[WARN ]: ", "[INFO ]: ", "[DEBUG]: "};

xsim::Logger::Logger(LogLevel logLevel) {
	message << LevelLogString[logLevel];
}

xsim::Logger::~Logger() {
	idl::console_write(message.str().c_str());
}