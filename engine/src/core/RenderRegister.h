#ifndef XSIM_RENDER_REGISTER_H
#define XSIM_RENDER_REGISTER_H

#include "defines.h"
#include <idl_render.h>
#include <unordered_set>
#include "BaseRenderer.h"

namespace xsim {

	class XSIM_API RenderRegister {
    private:
		static std::unordered_set<BaseRenderer*> renderers;
		static std::unordered_set<BaseRenderer*> no_init_renderers;
	public:
		static idl::Render* render;

        static void add(BaseRenderer*);
        static void remove(BaseRenderer*);
        static void initAll();
        static void drawAll();
        static void cleanUp();
	};

}  // namespace xsim
#endif