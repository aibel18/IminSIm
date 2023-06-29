#include "Application.h"
#include "util/logger.h"
#include <idl_window.h>

using namespace idl;

bool initialized = false;
static Context* context;
static idl_window* window;

xsim::Application::Application(GameBase* game) : game(game) {
}

bool xsim::Application::create() {

	if (initialized) {
		LOG_ERROR("Application create called more than once.");
		return false;
	}
	/* --- Initialize subsystems --- */

	// init log

	// init render context
	context = create_context(game->contextConf.type);
	if (!context || !context->init(game->contextConf.major, game->contextConf.minor)) {
		LOG_ERROR("Context was not created.");
		return false;
	}
	auto info = context->getInfo();
	LOG_INFO("renderer: %s", info.renderer);
	LOG_INFO("version : %s", info.version);

	// init render
	game->render = context->getRender();

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

	while (!idl::is_closed(window)) {
		idl::process_events(window);

		game->update();
		game->draw();

		context->swapInterval(window);
		context->swapBuffers(window);
	}

	game->end();

	context->destroyCurrent(window);

	destroy_window(window);
	destroy_context(context);
	return true;
}
