#include "idl_context.h"
#include "render/idl_opengl_context.h"

idl::Context::Context(GraphicRender type) : type(type) {
}

idl::Context::~Context() {
	if (!render)
		return;
	delete render;
}

idl::Context* idl::create_context(GraphicRender graphicContext) {

	switch (graphicContext) {
		case idl::IDL_OPENGL:
			return new OpenGLContext();
		default:
			return new OpenGLContext();
	}
}

void idl::destroy_context(Context* context) {
	if (!context)
		return;
	delete context;
}