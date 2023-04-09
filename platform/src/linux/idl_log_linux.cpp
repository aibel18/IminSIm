#include "idl_log.h"

#if IDL_LINUX_PLATFORM

#include <stdio.h>

const char* levels[] = {"1;31", "1;33", "1;32", "1;34"};  // ERROR, WARN, INFO, DEBUG

void idl::console_write(const char* message, int size, int level) {
	printf("\033[%sm%s\033[0m\n", levels[level], message);
}

#endif