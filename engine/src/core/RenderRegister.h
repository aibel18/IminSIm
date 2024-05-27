#ifndef XSIM_RENDER_REGISTER_H
#define XSIM_RENDER_REGISTER_H

#include "defines.h"
#include <idl_render.h>
#include <vector>
#include "BaseRenderer.h"

namespace xsim {

	class XSIM_API RenderRegister {
    private:
		static std::vector<BaseRenderer*> renderers;
	public:
		static idl::Render* render;

        static void pruning();
        static void add(BaseRenderer*);
        static void drawAll();
        static void cleanUp();
	};

}  // namespace xsim
#endif