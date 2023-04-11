#include "window.h"
#include "util/logger.h"

xsim::Window::Window(const char *name, int width, int height) : width(width), height(height) {
	handle = idl::create_window(name, this->width, this->height);
	LOG_INFO("create window %ix%i", this->width, this->height);
}

xsim::Window::~Window() {
	idl::destroy_window(handle);
	LOG_INFO("destroy window");
}

void xsim::Window::run() {

	while (!idl::is_closed(handle)) {
		idl::process_events(handle);
	}
}
