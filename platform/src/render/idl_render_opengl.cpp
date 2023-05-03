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

GLuint VertexArrayID;
static const GLfloat g_vertex_buffer_data[] = {
    -1.0f, -1.0f, 0.0f,
    1.0f,  -1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
};
bool once = false;
GLuint vertexbuffer;
void idl::RenderOpenGL::drawTriangle() {
	if (!once) {
		glGenVertexArrays(1, &VertexArrayID);
		glBindVertexArray(VertexArrayID);

		// This will identify our vertex buffer
		// Generate 1 buffer, put the resulting identifier in vertexbuffer
		glGenBuffers(1, &vertexbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		
		// Give our vertices to OpenGL.
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
		once = true;
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(
				0,         // attribute 0. No particular reason for 0, but must match the layout in the shader.
				3,         // size
				GL_FLOAT,  // type
				GL_FALSE,  // normalized?
				0,         // stride
				(void *)0  // array buffer offset
		);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	}
	glEnableVertexAttribArray(0);

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 3);  // Starting from vertex 0; 3 vertices total -> 1 triangle
	glDisableVertexAttribArray(0);
}