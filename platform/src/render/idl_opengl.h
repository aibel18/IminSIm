#ifndef IDL_OPENGL_H
#define IDL_OPENGL_H

// Load all OpenGL functions
#define GL_GLEXT_PROTOTYPES

#include "GL/glcorearb.h"

// Load only selected OpenGL functions
#ifndef GL_GLEXT_PROTOTYPES

#include "idl_defines.h"

namespace idl {

#define GL_FUNCTIONS(X)                                            \
	X(PFNGLCREATEBUFFERSPROC, glCreateBuffers)                       \
	X(PFNGLNAMEDBUFFERSTORAGEPROC, glNamedBufferStorage)             \
	X(PFNGLBINDVERTEXARRAYPROC, glBindVertexArray)                   \
	X(PFNGLCREATEVERTEXARRAYSPROC, glCreateVertexArrays)             \
	X(PFNGLVERTEXARRAYATTRIBBINDINGPROC, glVertexArrayAttribBinding) \
	X(PFNGLVERTEXARRAYVERTEXBUFFERPROC, glVertexArrayVertexBuffer)   \
	X(PFNGLVERTEXARRAYATTRIBFORMATPROC, glVertexArrayAttribFormat)   \
	X(PFNGLENABLEVERTEXARRAYATTRIBPROC, glEnableVertexArrayAttrib)   \
	X(PFNGLCREATESHADERPROGRAMVPROC, glCreateShaderProgramv)         \
	X(PFNGLGETPROGRAMIVPROC, glGetProgramiv)                         \
	X(PFNGLGETPROGRAMINFOLOGPROC, glGetProgramInfoLog)               \
	X(PFNGLGENPROGRAMPIPELINESPROC, glGenProgramPipelines)           \
	X(PFNGLUSEPROGRAMSTAGESPROC, glUseProgramStages)                 \
	X(PFNGLBINDPROGRAMPIPELINEPROC, glBindProgramPipeline)           \
	X(PFNGLPROGRAMUNIFORMMATRIX2FVPROC, glProgramUniformMatrix2fv)   \
	X(PFNGLBINDTEXTUREUNITPROC, glBindTextureUnit)                   \
	X(PFNGLCREATETEXTURESPROC, glCreateTextures)                     \
	X(PFNGLTEXTUREPARAMETERIPROC, glTextureParameteri)               \
	X(PFNGLTEXTURESTORAGE2DPROC, glTextureStorage2D)                 \
	X(PFNGLTEXTURESUBIMAGE2DPROC, glTextureSubImage2D)               \
	X(PFNGLDEBUGMESSAGECALLBACKPROC, glDebugMessageCallback)         \
	X(PFNGLCLEARCOLORPROC, glClearColor)                             \
	X(PFNGLGETSTRINGPROC, glGetString)                               \
	X(PFNGLCLEARPROC, glClear)

#define X(type, name) static type name;
	GL_FUNCTIONS(X)
#undef X

	static void LoadGLFunctions() {

#if defined(IDL_WINDOWS_PLATFORM)
		HMODULE module = LoadLibraryA("OpenGL32.dll");
#define X(type, name)                                                                                 \
	name = (type)wglGetProcAddress(#name);                                                              \
	if (name == 0 || name == (type)0x1 || name == (type)0x2 || name == (type)0x3 || name == (type)-1) { \
		name = (type)GetProcAddress(module, #name);                                                       \
	}
#else
#define X(type, name)
#endif
		GL_FUNCTIONS(X)
#undef X
	}

}  // namespace idl
#endif

#undef GL_GLEXT_PROTOTYPES

#endif
