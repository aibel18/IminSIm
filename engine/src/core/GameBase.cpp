#include "GameBase.h"
#include "GameRegister.h"

xsim::GameBase::GameBase() {
	GameRegister::game = this;
}

xsim::GameBase::~GameBase() {
}