#include "idl_window.h"

#if IDL_LINUX_PLATFORM

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>

namespace idl {

	struct idl_window final {
		Display* display;
		Atom deleteMessage;
		Window window;
		void * context;
		bool close = false;
	};
}  // namespace idl

#endif
