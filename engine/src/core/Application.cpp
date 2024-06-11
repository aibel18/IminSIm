#include "Application.h"
#include "util/logger.h"
#include <idl_context.h>
#include "RenderRegister.h"
#include "SimulatorRegister.h"

using namespace idl;

bool initialized = false;
static Context* context;
static idl_window* window;

xsim::Application::Application(BaseGame* game) : game(game) {
    LOG_DEBUG("Created Application");
}

xsim::Application::~Application() {
    LOG_DEBUG("Destroyed Application");
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
	LOG_INFO("glsl    : %s", info.glsl);
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

    LOG_DEBUG("Start main loop");

	while (!idl::is_closed(window)) {
		idl::process_events(window);

		game->update();
        SimulatorRegister::simulate(true);
        RenderRegister::drawAll();

		context->swapInterval(window);
		context->swapBuffers(window);
	}
    LOG_DEBUG("End main loop");

	game->end();

	return true;
}

bool xsim::Application::cleanUp() {
    SimulatorRegister::cleanUp();
    RenderRegister::cleanUp();
	context->destroyCurrent(window);

	destroy_window(window);
	destroy_context(context);
	return true;
}
