#ifndef IDL_RENDER_H
#define IDL_RENDER_H

#include "idl_defines.h"

namespace idl {

	struct IDL_API Render {
        u32 version;
		virtual ~Render(){};
		virtual void setClearColor(float r, float g, float v, float a = 1.0f) = 0;
		virtual void setColor(float r, float g, float v, float a = 1.0f) = 0;
		virtual void setViewPort(int width, int height) = 0;
		virtual void clear() = 0;
		virtual void getInfo(const u8 *&renderer, const u8 *&version, const u8 *&glsl) = 0;
		virtual void initData(u32 &vao, u32 &vbo, float *data, int size_bytes, bool modo = 0) = 0;
		virtual void updateData(u32 &vbo, float *data, int size_bytes) = 0;
		virtual void drawData(u32 &vao, int count) = 0;
		virtual void endData(u32 &vao, u32 &vbo) = 0;
        // option to minor than 3.0 version (only opengl)
		virtual void drawData(u32 &vao, float *data, int count) = 0;
	};
}  // namespace idl
#endif
