#ifndef XSIM_WINDOW_H
#define XSIM_WINDOW_H

#include "defines.h"
#include <idl_window.h>

namespace xsim {

	class XSIM_API Window {

	private:
		idl::idl_window* handle;

	private:
		int width;
		int height;

	public:
		Window(const char* name, int width = 1280, int height = 720);
		~Window();
		void run();
	};

}  // namespace xsim

#endif  // XSIM_WINDOW
