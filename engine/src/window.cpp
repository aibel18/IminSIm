#include "window.h"
#include "util/logger.h"
#include <idl_context.h>

idl::Context* context;

xsim::Window::Window(const char* name, int width, int height) : width(width), height(height) {
	context = idl::create_context(idl::IDL_OPENGL);
	context->init(3, 1);
	auto info = context->getInfo();

	LOG_INFO("renderer: %s", info.renderer);
	LOG_INFO("version : %s", info.version);
	LOG_INFO("glsl : %s", info.glsl);

	handle = idl::create_window(name, this->width, this->height);
	LOG_INFO("create window %ix%i", this->width, this->height);
}

xsim::Window::~Window() {
	idl::destroy_window(handle);
	idl::destroy_context(context);
	LOG_INFO("destroy window");
}

void xsim::Window::run() {
	auto render = context->getRender();

	auto handle2 = idl::create_window("Other window", this->width, this->height);

	context->makeCurrent(handle);
	render->setColor(0.392f, 0.584f, 0.929f);
	context->makeCurrent(handle2);
	render->setColor(0.322f, 0.2f, 0.f);

	while (!(idl::is_closed(handle) || idl::is_closed(handle2))) {
		idl::process_events(handle);
		idl::process_events(handle2);

		context->swapInterval();
		context->swapBuffers(handle);
		context->swapBuffers(handle2);
	}
	idl::destroy_window(handle2);
}
