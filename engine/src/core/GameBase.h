#ifndef XSIM_GAME_BASE_H
#define XSIM_GAME_BASE_H

#include "defines.h"
#include "ApplicationConfig.h"
#include <idl_render.h>

namespace xsim {

	class XSIM_API GameBase {
	public:
		ApplicationConfig config;
		idl::Render* render;

	public:
		virtual ~GameBase() = 0;

	protected:
		virtual void init() = 0;
		virtual void update() = 0;
		virtual void draw() = 0;
		virtual void onResize(int width, int height) = 0;

		friend class Application;
	};

}  // namespace xsim
#endif