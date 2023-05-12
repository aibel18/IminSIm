#include "idl_render_opengl.h"
#include "idl_opengl.h"

idl::RenderOpenGL::RenderOpenGL() {
	load_opengl_functions();
}
void idl::RenderOpenGL::setClearColor(float r, float g, float v, float a) {
	glClearColor(r, g, v, a);
}
void idl::RenderOpenGL::setColor(float r, float g, float v, float a) {
	glColor4f(r, g, v, a);
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

void idl::RenderOpenGL::initSimpleDraw(u32 &vao, u32 &vbo, float *points, int size, int count, bool modo) {

	// VAO
	glGenVertexArrays(1, &vao);  // create VAO
	glBindVertexArray(vao);      // bind VAO

	// VBO
	glGenBuffers(1, &vbo);               // create VBO
	glBindBuffer(GL_ARRAY_BUFFER, vbo);  // bind VBO

	if (modo)
		glBufferData(GL_ARRAY_BUFFER, size, points, GL_DYNAMIC_DRAW);
	else
		glBufferData(GL_ARRAY_BUFFER, size, points, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);  // enable attribute 0
	glVertexAttribPointer(
	    0,         // attribute 0.
	    count,     // size
	    GL_FLOAT,  // type
	    GL_FALSE,  // normalized?
	    0,         // stride
	    (void *)0  // array buffer offset
	);
	glDisableVertexAttribArray(0);  // disable attribute 0

	glBindBuffer(GL_ARRAY_BUFFER, 0);  // unbind VBO
	glBindVertexArray(0);              // unbind VAO
}

void idl::RenderOpenGL::updateSimpleDraw(u32 &vbo, float *points, int size) {
	glBindBuffer(GL_ARRAY_BUFFER, vbo);  // bind VBO
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, points);
	glBindBuffer(GL_ARRAY_BUFFER, 0);  // unbind VBO
}

void idl::RenderOpenGL::drawSimple(u32 &vao, int count) {
	glBindVertexArray(vao);  // bind VAO

	glEnableVertexAttribArray(0);           // enable attribute 0.
	glDrawArrays(GL_LINE_STRIP, 0, count);  // Starting from vertex 0; count vertices total
	glDisableVertexAttribArray(0);          // disable attribute 0.

	glBindVertexArray(0);  // unbind VAO
}

void idl::RenderOpenGL::endSimpleDraw(u32 &vao, u32 &vbo) {
	glDeleteBuffers(1, &vbo);       // delete VBO
	glDeleteVertexArrays(1, &vao);  // delete VAO
}
