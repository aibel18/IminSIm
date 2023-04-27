#ifndef IDL_RENDER_OPENGL_H
#define IDL_RENDER_OPENGL_H

#include "idl_render.h"

namespace idl {

	struct RenderOpenGL : Render {
		RenderOpenGL();
		void setColor(float r, float g, float v);
		void setViewPort(int width, int height);
		void clear();
		void getInfo(const u8*& renderer, const u8*& version, const u8*& glsl);
	};
}  // namespace idl
#endif
