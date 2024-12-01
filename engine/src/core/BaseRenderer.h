#ifndef XSIM_BASE_RENDERER_H
#define XSIM_BASE_RENDERER_H

#include "defines.h"

namespace xsim {

	class XSIM_API BaseRenderer {
	public:
		BaseRenderer();
		virtual ~BaseRenderer() = 0;

	protected:
		virtual void init() = 0;
		virtual void draw() = 0;

    private:

		friend class RenderRegister;
	};

}  // namespace xsim
#endif