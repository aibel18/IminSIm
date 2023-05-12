#ifndef XSIM_GAME_REGISTER_H
#define XSIM_GAME_REGISTER_H

#include "defines.h"
#include "core/GameBase.h"

namespace xsim {

	class XSIM_API GameRegister {
	public:
		static GameBase *game;
	};

}  // namespace xsim
#endif