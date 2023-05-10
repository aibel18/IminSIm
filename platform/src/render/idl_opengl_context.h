#ifndef IDL_OPENGL_CONTEXT_H
#define IDL_OPENGL_CONTEXT_H

#include "idl_context.h"

namespace idl {

	class OpenGLContext : public Context {

	private:
		bool isExtFunctionsLoaded();
		bool loadExtFunctions(u8 colorBits, u8 depthBits);

	public:
		OpenGLContext();
		bool init(int major, int minor, u8 color, u8 depth);
		bool makeCurrent(idl_window* window);
		bool swapInterval(idl_window* window);
		bool swapBuffers(idl_window* window);
		bool destroyCurrent(idl_window* window);
		ContextInfo getInfo();
	};

}  // namespace idl
#endif
