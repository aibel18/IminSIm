#include "idl_log.h"

#if IDL_WINDOWS_PLATFORM

#include <windows.h>

const int levels[4] = {4, 6, 2, 1};  // ERROR, WARN, INFO, DEBUG
HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
LPDWORD number_written = 0;

void idl::console_write(const char *message, int size, int level) {
	SetConsoleTextAttribute(consoleHandle, levels[level]);
	WriteConsoleA(consoleHandle, message, size, number_written, 0);
	WriteConsoleA(consoleHandle, "\n", 1, number_written, 0);
	OutputDebugStringA(message);
	SetConsoleTextAttribute(consoleHandle, 7);  // DEFAULT
}

#endif