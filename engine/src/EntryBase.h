#include "core/Application.h"
#include "core/GameBase.h"
#include "util/logger.h"

using namespace xsim;

extern GameBase* CreateGame();
extern void DestroyGame(GameBase* game);

int main() {

	// Request the game instance
	GameBase* game = CreateGame();

	if (!game) {
		LOG_ERROR("Game was not created");
		return -1;
	}

	Application app(game);
	if (app.create()) {
		app.run();
	}

	// Request to destroy the game instance
	DestroyGame(game);

	return 0;
}