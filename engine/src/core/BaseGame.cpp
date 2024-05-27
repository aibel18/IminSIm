#include "BaseGame.h"
#include "GameRegister.h"
#include "util/logger.h"

xsim::BaseGame::BaseGame() {
	GameRegister::game = this;
    LOG_DEBUG("Created BaseGame");
}

xsim::BaseGame::~BaseGame() {
    LOG_DEBUG("Destroyed BaseGame");
}