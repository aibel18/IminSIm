#ifndef XSIM_APPLICATION_H
#define XSIM_APPLICATION_H

#include "defines.h"
#include "BaseGame.h"

namespace xsim {

	class XSIM_API Application {
	private:
		BaseGame* game;

	public:
		Application(BaseGame* game);
		bool create();
		bool run();
	};
}  // namespace xsim
#endif