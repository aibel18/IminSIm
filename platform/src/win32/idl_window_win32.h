#include "idl_window.h"

#if IDL_WINDOWS_PLATFORM

#include <windows.h>

namespace idl {

	struct idl_window final{
		HINSTANCE instance;
		HWND handle;
		bool close = false;
	};

	LRESULT CALLBACK process_event(HWND hwnd, unsigned int msg, WPARAM wParam, LPARAM lParam);

}  // namespace idl

#endif
