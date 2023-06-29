#ifndef IDL_OPENGL_H
#define IDL_OPENGL_H

#include "idl_defines.h"
#include "GL/glcorearb.h"

#if defined(IDL_WINDOWS_PLATFORM)
#include <gl/GL.h>
#include "GL/wglext.h"
#elif defined(IDL_LINUX_PLATFORM)
#include <GL/glx.h>
#include "GL/glxext.h"
#else
// other platforms
#endif

// Load only selected OpenGL functions
#define GL_FUNCTIONS                                               \
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
	X(PFNGLGENVERTEXARRAYSPROC, glGenVertexArrays)                   \
	X(PFNGLGENBUFFERSPROC, glGenBuffers)                             \
	X(PFNGLBINDBUFFERPROC, glBindBuffer)                             \
	X(PFNGLBUFFERDATAPROC, glBufferData)                             \
	X(PFNGLENABLEVERTEXATTRIBARRAYPROC, glEnableVertexAttribArray)   \
	X(PFNGLDISABLEVERTEXATTRIBARRAYPROC, glDisableVertexAttribArray) \
	X(PFNGLVERTEXATTRIBPOINTERPROC, glVertexAttribPointer)           \
	X(PFNGLDELETEBUFFERSPROC, glDeleteBuffers)                       \
	X(PFNGLDELETEVERTEXARRAYSPROC, glDeleteVertexArrays)             \
	X(PFNGLBUFFERSUBDATAPROC, glBufferSubData)

#define X(type, name) extern type name;
GL_FUNCTIONS
#undef X

namespace idl {

	void load_opengl_functions();

}  // namespace idl
#endif
