#include "logger.h"

const char* xsim::LogLevelString[4] = {"[ERROR]: ", "[WARN ]: ", "[INFO ]: ", "[DEBUG]: "};
xsim::Logger xsim::logger;

xsim::Logger::Logger() {
}

void xsim::Logger::write(LogLevel level, const char *line, int size) {
	idl::console_write(line, size, level);
}
