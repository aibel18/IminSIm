#ifndef XSIM_BASE_GAME_H
#define XSIM_BASE_GAME_H

#include "defines.h"
#include "ApplicationConfig.h"
#include "ContextConfig.h"

namespace xsim {

	class XSIM_API BaseGame {
	public:
		ApplicationConfig appConf;
		ContextConfig contextConf;

	public:
		BaseGame();
		virtual ~BaseGame() = 0;

	protected:
		virtual void init() {};
		virtual void update() {};
		virtual void end() {};
		virtual void onResize(int width, int height) {};

		friend class Application;
	};

}  // namespace xsim
#endif
