#ifndef XSIM_BASE_RENDERER_H
#define XSIM_BASE_RENDERER_H

#include "defines.h"

namespace xsim {

	class XSIM_API BaseRenderer {
	public:
		BaseRenderer();
		virtual ~BaseRenderer() = 0;

	protected:
		virtual void draw() = 0;

		friend class Application;
	};

}  // namespace xsim
#endif