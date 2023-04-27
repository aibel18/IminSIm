#include "idl_render_opengl.h"
#include "idl_opengl.h"

idl::RenderOpenGL::RenderOpenGL() {
	load_opengl_functions();
}
void idl::RenderOpenGL::setColor(float r, float g, float v) {
	glClearColor(r, g, v, 1.f);
}

void idl::RenderOpenGL::setViewPort(int width, int height) {
	glViewport(0, 0, width, height);
}

void idl::RenderOpenGL::clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void idl::RenderOpenGL::getInfo(const u8 *&renderer, const u8 *&version, const u8 *&glsl) {
	renderer = glGetString(GL_RENDERER);
	version = glGetString(GL_VERSION);
	glsl = glGetString(GL_SHADING_LANGUAGE_VERSION);
}
