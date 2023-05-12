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
		void initSimpleDraw(u32 &vao, u32 &vbo, float *points, int size, int count, bool modo);
		void updateSimpleDraw(u32 &vbo, float *points, int size);
		void drawSimple(u32 &vao, int count);
		void endSimpleDraw(u32 &vao, u32 &vbo);
	};
}  // namespace idl
#endif
