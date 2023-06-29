#ifndef IDL_RENDER_OPENGL_H
#define IDL_RENDER_OPENGL_H

#include "idl_render.h"

namespace idl {

	struct RenderOpenGL : Render {
		RenderOpenGL();
		void setClearColor(float r, float g, float v, float a);
		void setColor(float r, float g, float v, float a);
		void setViewPort(int width, int height);
		void clear();
		void getInfo(const u8 *&renderer, const u8 *&version, const u8 *&glsl);
		void initData(u32 &vao, u32 &vbo, float *data, int size_bytes, bool modo);
		void updateData(u32 &vbo, float *data, int size_bytes);
		void drawData(u32 &vao, int count);
		void endData(u32 &vao, u32 &vbo);
	};
}  // namespace idl
#endif
