#include "window.h"
#include "util/logger.h"
#include <idl_context.h>

idl::Context* context;

xsim::Window::Window(const char *name, int width, int height) : width(width), height(height) {
	context = idl::create_context(idl::IDL_OPENGL);
	context->init(3, 4);
	
	handle = idl::create_window(name, this->width, this->height);
	LOG_INFO("create window %ix%i", this->width, this->height);
}

xsim::Window::~Window() {
	idl::destroy_window(handle);
	idl::destroy_context(context);
	LOG_INFO("destroy window");
}

void xsim::Window::run() {

	context->makeCurrent(handle);
	auto info = context->getInfo();

	LOG_INFO("renderer: %s", info.renderer);
	LOG_INFO("version : %s", info.version);
	LOG_INFO("glsl : %s", info.glsl);

	while (!idl::is_closed(handle)) {
		idl::process_events(handle);
		context->swapBuffers(handle);
	}
}
