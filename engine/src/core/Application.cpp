#include "Application.h"
#include "util/logger.h"
#include <idl_context.h>
#include <idl_window.h>

using namespace idl;

bool initialized = false;
static Context* context;
static Render* render;
static idl_window* window;

bool xsim::Application::create(ApplicationConfig* config) {

	if (initialized) {
		LOG_ERROR("Application create called more than once.");
		return false;
	}

	/* --- Initialize subsystems --- */

	// init log

	// init render context
	context = create_context(IDL_OPENGL);
	if (!context || !context->init(3, 1)) {
		LOG_ERROR("Context was not created.");
		return false;
	}
	auto info = context->getInfo();
	LOG_INFO("renderer: %s", info.renderer);
	LOG_INFO("version : %s", info.version);

	// init render
	render = context->getRender();

	// init window
	window = create_window(config->name, config->width, config->height);
	if (!window) {
		LOG_ERROR("Window was not created.");
		return false;
	}
	LOG_INFO("create window %ix%i", config->width, config->height);

	// set context on window
	if(!context->makeCurrent(window)){
		LOG_ERROR("Context was not assigned to the window.");
		return false;
	}

	initialized = true;
	this->config = config;
	return true;
}

bool xsim::Application::run() {

	if (!initialized) {
		return false;
	}

	render->setColor(0.392f, 0.584f, 0.929f);

	while (!idl::is_closed(window)) {
		idl::process_events(window);

		render->clear();
		render->drawTriangle();

		context->swapInterval();
		context->swapBuffers(window);
	}

	destroy_window(window);
	destroy_context(context);
	return true;
}
