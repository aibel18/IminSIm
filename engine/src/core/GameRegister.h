#ifndef XSIM_GAME_REGISTER_H
#define XSIM_GAME_REGISTER_H

#include "defines.h"
#include "core/BaseGame.h"

namespace xsim {

	class XSIM_API GameRegister {
	public:
		static BaseGame *game;
	};

}  // namespace xsim
#endif