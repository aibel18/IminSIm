#include "core/Application.h"
#include "util/logger.h"

using namespace xsim;

extern BaseGame* createGame();

int main() {

	// Request the game instance
	BaseGame* game = createGame();

	if (!game) {
		LOG_ERROR("Game was not created");
		return -1;
	}

	Application app(game);
	if (app.create()) {
		app.run();
        delete game;
        app.cleanUp();
	}

	return 0;
}