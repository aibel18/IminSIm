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
		virtual void init() = 0;
		virtual void update() = 0;
		virtual void end() = 0;
		virtual void onResize(int width, int height) = 0;

		friend class Application;
	};

}  // namespace xsim
#endif