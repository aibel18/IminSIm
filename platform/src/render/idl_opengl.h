#ifndef IDL_OPENGL_H
#define IDL_OPENGL_H

// Load all OpenGL functions
#define GL_GLEXT_PROTOTYPES

#include "GL/glcorearb.h"

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
	X(PFNGLDEBUGMESSAGECALLBACKPROC, glDebugMessageCallback)

#define X(type, name) static type name;
	GL_FUNCTIONS(X)
#undef X

	// Load only selected OpenGL functions
	void load_custom_openGL() {
		// TODO: verify platform
#define X(type, name) name = (type)wglGetProcAddress(#name);
		GL_FUNCTIONS(X)
#undef X
	}

}  // namespace idl
#endif
