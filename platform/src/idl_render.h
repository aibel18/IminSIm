#ifndef IDL_RENDER_H
#define IDL_RENDER_H

#include "idl_defines.h"

namespace idl {

	struct IDL_API Render {
		virtual ~Render(){};
		virtual void setClearColor(float r, float g, float v, float a = 1.0f) = 0;
		virtual void setColor(float r, float g, float v, float a = 1.0f) = 0;
		virtual void setViewPort(int width, int height) = 0;
		virtual void clear() = 0;
		virtual void getInfo(const u8 *&renderer, const u8 *&version, const u8 *&glsl) = 0;
		virtual void initSimpleDraw(u32 &vao, u32 &vbo, float *points, int size, int count, bool modo) = 0;
		virtual void updateSimpleDraw(u32 &vbo, float *points, int size) = 0;
		virtual void drawSimple(u32 &vao, int count) = 0;
		virtual void endSimpleDraw(u32 &vao, u32 &vbo) = 0;
	};
}  // namespace idl
#endif
