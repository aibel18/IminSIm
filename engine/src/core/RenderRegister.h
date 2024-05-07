#ifndef XSIM_RENDER_REGISTER_H
#define XSIM_RENDER_REGISTER_H

#include "defines.h"
#include <idl_render.h>
#include <vector>
#include "BaseRenderer.h"

namespace xsim {

	class XSIM_API RenderRegister {
	public:
		static idl::Render* render;
		static std::vector<BaseRenderer*> renderers;
	};

}  // namespace xsim
#endif