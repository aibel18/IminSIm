#ifndef XSIM_BASE_RENDERER_H
#define XSIM_BASE_RENDERER_H

#include "defines.h"
#include <vector>
#include "math/math_defines.h"

namespace xsim {

	class XSIM_API BaseRenderer {
	public:
		BaseRenderer();
		virtual ~BaseRenderer() = 0;

		std::vector<vec3> data;
		virtual void update() = 0;
	protected:
		virtual void init() = 0;
		virtual void draw() = 0;

    private:
        bool isInit;
        void initSuper();

		friend class RenderRegister;
	};

}  // namespace xsim
#endif