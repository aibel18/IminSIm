#ifndef IDL_WINDOW_H
#define IDL_WINDOW_H

#include "idl_defines.h"

namespace idl {

	struct idl_window;

	IDL_API idl_window* create_window(const char* name, int width, int height);
	IDL_API void process_events(idl_window* window);
	IDL_API void destroy_window(idl_window* window);
	IDL_API bool is_closed(idl_window* window);

}  // namespace idl
#endif