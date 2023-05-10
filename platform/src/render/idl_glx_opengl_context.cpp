#include "idl_opengl_context.h"

#if IDL_LINUX_PLATFORM

#include "linux/idl_window_linux.h"
#include "idl_render_opengl.h"
#include "idl_opengl.h"
#include <stdio.h>  // TODO: remove when add exception manager

int pixelFormat;
int glxContextAttribs[16];
GLXFBConfig glxConfig;

#define GLX_MAJOR_MIN 1
#define GLX_MINOR_MIN 2

#define GLX_FUNCTIONS                                              \
	W(PFNGLXCREATECONTEXTATTRIBSARBPROC, glXCreateContextAttribsARB) \
	W(PFNGLXSWAPINTERVALEXTPROC, glXSwapIntervalEXT)

#define W(type, name) type name = 0;
GLX_FUNCTIONS
#undef W

// TODO: Trow exception and log about no initialized context
#define IS_OPENGL_INIT \
	if (!initialized) {  \
		return false;      \
	}

bool idl::OpenGLContext::isExtFunctionsLoaded() {
	if (!glXCreateContextAttribsARB || !glXSwapIntervalEXT) {
		return false;
	}
	return true;
}

bool idl::OpenGLContext::loadExtFunctions(u8 colorBits, u8 depthBits) {

	if (isExtFunctionsLoaded()) {
		return true;
	}

#define W(type, name) name = (type)glXGetProcAddressARB((const GLubyte *)#name);
	GLX_FUNCTIONS
#undef W

	if (!isExtFunctionsLoaded()) {
		// TODO: Add Exception Manager
		printf("OpenGL don't support WGL extensions!\n");
		return false;
	}

	return true;
}

idl::OpenGLContext::OpenGLContext() : Context(IDL_OPENGL) {
}

bool idl::OpenGLContext::init(int major, int minor, u8 color, u8 depth) {

	if (!loadExtFunctions(color, depth)) {
		initialized = false;
		return false;
	}

	const int pixelAttribs[] = {
	    GLX_X_RENDERABLE, GL_TRUE,
	    GLX_X_VISUAL_TYPE, GLX_TRUE_COLOR,
	    GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
	    // GLX_SUPPORT_OPENGL_ARB,  GL_TRUE,
	    GLX_DOUBLEBUFFER, GL_TRUE,
	    GLX_RENDER_TYPE, GLX_RGBA_BIT,
	    GLX_RED_SIZE, color / 4,
	    GLX_GREEN_SIZE, color / 4,
	    GLX_BLUE_SIZE, color / 4,
	    // GLX_ALPHA_SIZE, color/4,
	    GLX_DEPTH_SIZE, depth,
	    GLX_STENCIL_SIZE, 8,
	    0,
	};

	const int contextAttribs[] = {
		GLX_CONTEXT_MAJOR_VERSION_ARB, major,
		GLX_CONTEXT_MINOR_VERSION_ARB, minor,
		GLX_CONTEXT_PROFILE_MASK_ARB,	GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
#if LOG_DEBUG_ENABLED
		GLX_CONTEXT_FLAGS_ARB, GLX_CONTEXT_DEBUG_BIT_ARB,
#endif
		0,
	};

	memcpy(glxContextAttribs, contextAttribs, sizeof(contextAttribs));

	Display *display = XOpenDisplay(0);

	if (!display) {
		// TODO: Add Exception Manager
		printf("Window creation failed for dummy!");
		return false;
	}

	GLint glxMajor, glxMinor;
	glXQueryVersion(display, &glxMajor, &glxMinor);

	if (glxMajor < GLX_MAJOR_MIN || (glxMajor == GLX_MAJOR_MIN && glxMinor < GLX_MINOR_MIN)) {
		printf("GLX 1.2 or greater is required");
		XCloseDisplay(display);
		return false;
	}

	int fbcCount = 0;
	GLXFBConfig *fbcConfig = glXChooseFBConfig(display, DefaultScreen(display), pixelAttribs, &fbcCount);

	if (!fbcConfig || fbcCount == 0) {
		// TODO: Add Exception Manager
		printf("Failed to retrieve framebuffer configs!");
		XCloseDisplay(display);
		return false;
	}

	int selectedConfigId = -1;
	int bestSamples = -1;

	for (int i = 0; i < fbcCount; i++) {
		XVisualInfo *visualInfo = glXGetVisualFromFBConfig(display, fbcConfig[i]);

		if (visualInfo) {
			int sampleBuffers;
			int samples;

			glXGetFBConfigAttrib(display, fbcConfig[i], GLX_SAMPLE_BUFFERS, &sampleBuffers);
			glXGetFBConfigAttrib(display, fbcConfig[i], GLX_SAMPLES, &samples);

			if (selectedConfigId < 0 || (sampleBuffers && samples > bestSamples)) {
				selectedConfigId = i;
				bestSamples = samples;
			}

			XFree(visualInfo);
		}
	}
	glxConfig = fbcConfig[selectedConfigId];
	XFree(fbcConfig);

	Window dummy = XCreateSimpleWindow(display, DefaultRootWindow(display), 0, 0, 1, 1, 0, 0, 0);

	if (!dummy) {
		// TODO: Add Exception Manager
		printf("Window creation failed for dummy!");
		XCloseDisplay(display);
		return false;
	}

	GLXContext context = glXCreateContextAttribsARB(display, glxConfig, 0, true, glxContextAttribs);

	if (!context || !glXMakeCurrent(display, dummy, context)) {
		// TODO: Add Exception Manager
		printf("Context Creation failed");
		XDestroyWindow(display, dummy);
		XCloseDisplay(display);
		return false;
	}

	render = new RenderOpenGL();
	render->getInfo(info.renderer, info.version, info.glsl);

	initialized = true;

	glXMakeCurrent(display, 0, 0);
	// glXDestroyContext(display, context);
	XDestroyWindow(display, dummy);
	XCloseDisplay(display);

	return true;
}

bool idl::OpenGLContext::makeCurrent(idl_window *window) {

	if (window->context && glXMakeCurrent(window->display, window->window, (GLXContext)window->context))
		return true;

	IS_OPENGL_INIT

	window->context = glXCreateContextAttribsARB(window->display, glxConfig, 0, true, glxContextAttribs);

	if (!window->context || !glXMakeCurrent(window->display, window->window, (GLXContext)window->context)) {
		// TODO: Add Exception Manager
		printf("Context Creation failed\n");
		return false;
	}

	return true;
}

bool idl::OpenGLContext::swapInterval(idl_window *window) {
	bool vsync = true;
	glXSwapIntervalEXT(window->display, window->window, vsync ? 1 : 0);
	return false;
}

bool idl::OpenGLContext::swapBuffers(idl_window *window) {

	IS_OPENGL_INIT
	glXSwapBuffers(window->display, window->window);
	return true;
}

bool idl::OpenGLContext::destroyCurrent(idl_window *window) {
	if (window->context) {
		glXMakeCurrent(window->display, 0, 0);
		glXDestroyContext(window->display, (GLXContext)window->context);
	}
	window->context = 0;
	return true;
}

idl::ContextInfo idl::OpenGLContext::getInfo() {
	return info;
}

#endif