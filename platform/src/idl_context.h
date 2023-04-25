#ifndef IDL_CONTEXT_H
#define IDL_CONTEXT_H

#include "idl_defines.h"
#include "idl_window.h"
#include "idl_render.h"

namespace idl {

	enum GraphicRender {
		IDL_NONE,
		IDL_OPENGL,
		IDL_EGL_OPENGL,
		IDL_OSMESA,
		IDL_VULKAN,
		IDL_DIRECT_3D,
		IDL_METAL
	};

	struct ContextInfo {
		const u8* renderer = 0;
		const u8* version = 0;
		const u8* glsl = 0;
	};

	class IDL_API Context {

	protected:
		GraphicRender type;
		bool initialized = false;
		ContextInfo info;
		Render *render;

	public:
		Context(GraphicRender type);
		virtual ~Context() = 0;
		virtual bool init(int minor, int major, u8 color = 32, u8 depth = 24) = 0;
		virtual bool makeCurrent(idl_window* window) = 0;
		virtual bool swapBuffers(idl_window* window) = 0;
		virtual ContextInfo getInfo() = 0;
	};

	IDL_API Context* create_context(GraphicRender type);
	IDL_API void destroy_context(Context* context);

}  // namespace idl
#endif
