#ifndef XSIM_APPLICATION_H
#define XSIM_APPLICATION_H

#include "defines.h"
#include "GameBase.h"

namespace xsim {

	class XSIM_API Application {
	private:
		GameBase* game;

	public:
		Application(GameBase* game);
		bool create();
		bool run();
	};
}  // namespace xsim
#endif