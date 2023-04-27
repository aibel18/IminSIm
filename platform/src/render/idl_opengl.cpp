#include "idl_opengl.h"

#define X(type, name) type name;
GL_FUNCTIONS
#undef X

void idl::load_opengl_functions() {

#if defined(IDL_WINDOWS_PLATFORM)
	HMODULE module = LoadLibraryA("OpenGL32.dll");
#define X(type, name)                                                                                 \
	name = (type)wglGetProcAddress(#name);                                                              \
	if (name == 0 || name == (type)0x1 || name == (type)0x2 || name == (type)0x3 || name == (type)-1) { \
		name = (type)GetProcAddress(module, #name);                                                       \
	}
#else
// other platforms
#define X(type, name)
#endif

	GL_FUNCTIONS
#undef X

#if defined(IDL_WINDOWS_PLATFORM)
	FreeLibrary(module);
#else
// other platforms
#endif
}