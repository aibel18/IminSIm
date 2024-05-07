#include "Application.h"
#include "util/logger.h"
#include <idl_context.h>
#include "RenderRegister.h"

using namespace idl;

bool initialized = false;
static Context* context;
static idl_window* window;

xsim::Application::Application(BaseGame* game) : game(game) {
}

bool xsim::Application::create() {

	if (initialized) {
		LOG_ERROR("Application create called more than once.");
		return false;
	}
	/* --- Initialize subsystems --- */

	// init log

	// init render context
	context = create_context();
	if (!context || !context->init(game->contextConf.major, game->contextConf.minor)) {
		LOG_ERROR("Context was not created.");
		return false;
	}
	auto info = context->getInfo();
	LOG_INFO("renderer: %s", info.renderer);
	LOG_INFO("version : %s", info.version);

	// init render
	RenderRegister::render = context->getRender();

	// init window
	window = create_window(game->appConf.name, game->appConf.width, game->appConf.height);
	if (!window) {
		LOG_ERROR("Window was not created.");
		return false;
	}
	LOG_INFO("create window %ix%i", game->appConf.width, game->appConf.height);

	// set context on window
	if (!context->makeCurrent(window)) {
		LOG_ERROR("Context was not assigned to the window.");
		return false;
	}

	/* --- Initialize game --- */
	game->init();
	game->onResize(game->appConf.width, game->appConf.height);

	initialized = true;
	return true;
}

bool xsim::Application::run() {

	if (!initialized) {
		return false;
	}

	RenderRegister::render->setClearColor(0.392f, 0.584f, 0.929f);  // TODO: move this in other side

	while (!idl::is_closed(window)) {
		RenderRegister::render->clear();  // TODO: move this in other side
		idl::process_events(window);

		game->update();

		// call draw function of all renderers
		for (auto& r : RenderRegister::renderers) {
			r->draw();
		}

		context->swapInterval(window);
		context->swapBuffers(window);
	}

	// call destructor of all renderers
	for (auto& r : RenderRegister::renderers) {
		delete r;
		r = 0;
	}
	RenderRegister::renderers.clear(); // TODO: verify if it's necessary this line

	game->end();

	context->destroyCurrent(window);

	destroy_window(window);
	destroy_context(context);
	return true;
}
