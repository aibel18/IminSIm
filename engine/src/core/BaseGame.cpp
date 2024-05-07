#include "BaseGame.h"
#include "GameRegister.h"

xsim::BaseGame::BaseGame() {
	GameRegister::game = this;
}

xsim::BaseGame::~BaseGame() {
}