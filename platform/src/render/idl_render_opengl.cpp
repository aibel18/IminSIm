#include "idl_render_opengl.h"
#include "idl_opengl.h"

idl::RenderOpenGL::RenderOpenGL() {
	load_opengl_functions();
    auto stringVersion = glGetString(GL_VERSION);
    // converting literal version to int e.g '3.3' -> 33
    version = (stringVersion[0] - '0') * 10 + (stringVersion[2] - '0');
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

void idl::RenderOpenGL::initData(u32 &vao, u32 &vbo, float *data, int size_bytes, bool modo) {

	// VAO
	glGenVertexArrays(1, &vao);  // create VAO
	glBindVertexArray(vao);      // bind VAO

	// VBO
	glGenBuffers(1, &vbo);               // create VBO
	glBindBuffer(GL_ARRAY_BUFFER, vbo);  // bind VBO

	glBufferData(GL_ARRAY_BUFFER, size_bytes, data, modo ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);  // enable attribute 0
	glVertexAttribPointer(
	    0,         // attribute 0.
	    3,				 // size of elements : default 3 elements for vec3
	    GL_FLOAT,  // type
	    GL_FALSE,  // normalized?
	    0,         // stride
	    (void *)0  // array buffer offset
	);
	glDisableVertexAttribArray(0);  // disable attribute 0

	glBindBuffer(GL_ARRAY_BUFFER, 0);  // unbind VBO
	glBindVertexArray(0);              // unbind VAO
}

void idl::RenderOpenGL::updateData(u32 &vbo, float *data, int size_bytes) {
	glBindBuffer(GL_ARRAY_BUFFER, vbo);  // bind VBO
	glBufferSubData(GL_ARRAY_BUFFER, 0, size_bytes, data);
	glBindBuffer(GL_ARRAY_BUFFER, 0);  // unbind VBO
}

void idl::RenderOpenGL::drawData(u32 &vao, int count) {
	glBindVertexArray(vao);  // bind VAO

  glPointSize(10.f);
	glEnableVertexAttribArray(0);           // enable attribute 0.
	glDrawArrays(GL_POINTS, 0, count);  // Starting from vertex 0; count vertices total
	glDisableVertexAttribArray(0);          // disable attribute 0.

	glBindVertexArray(0);  // unbind VAO
}

void idl::RenderOpenGL::endData(u32 &vao, u32 &vbo) {
	glDeleteBuffers(1, &vbo);       // delete VBO
	glDeleteVertexArrays(1, &vao);  // delete VAO
}

void idl::RenderOpenGL::drawData(u32 &vao,float *data, int count) {
	glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, data);

    glDrawArrays(GL_LINE_STRIP, 0, count);

    glDisableClientState(GL_VERTEX_ARRAY);
}