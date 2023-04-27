#ifndef IDL_RENDER_H
#define IDL_RENDER_H

#include "idl_defines.h"

namespace idl {

	struct IDL_API Render {
		virtual ~Render(){};
		virtual void setColor(float r, float g, float v) = 0;
		virtual void setViewPort(int width, int height) = 0;
		virtual void clear() = 0;
		virtual void getInfo(const u8*& renderer, const u8*& version, const u8*& glsl) = 0;
	};
}  // namespace idl
#endif
