#include "core/Application.h"
#include "core/GameRegister.h"
#include "util/logger.h"

using namespace xsim;

int main() {

	// Request the game instance
	GameBase* game = GameRegister::game;

	if (!game) {
		LOG_ERROR("Game was not created");
		return -1;
	}

	Application app(game);
	if (app.create()) {
		app.run();
	}

	return 0;
}