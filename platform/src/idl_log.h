#ifndef IDL_LOG_H
#define IDL_LOG_H

#include "idl_defines.h"

namespace idl {

	IDL_API void console_write(const char *message, int size, int level);

	template <typename... Args>
	inline int Format(char *buffer, int bufferCount, const char *format, const Args &...args) {
		int result = snprintf(buffer, bufferCount, format, args...);
		return result;
	};

}  // namespace idl
#endif