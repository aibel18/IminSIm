#include "idl_opengl_context.h"

#if IDL_WINDOWS_PLATFORM

#include "win32/idl_window_win32.h"
#include "idl_render_opengl.h"
#include "idl_opengl.h"

int pixelFormat;
int wglContextAttribs[16];

#define WGL_FUNCTIONS                                              \
	W(PFNWGLCHOOSEPIXELFORMATARBPROC, wglChoosePixelFormatARB)       \
	W(PFNWGLCREATECONTEXTATTRIBSARBPROC, wglCreateContextAttribsARB) \
	W(PFNWGLSWAPINTERVALEXTPROC, wglSwapIntervalEXT)

#define W(type, name) type name;
WGL_FUNCTIONS
#undef W

// TODO: Trow exception and log about no initialized context
#define IS_OPENGL_INIT \
	if (!initialized) {  \
		return false;      \
	}

bool idl::OpenGLContext::isExtFunctionsLoaded() {
	if (!wglChoosePixelFormatARB || !wglCreateContextAttribsARB || !wglSwapIntervalEXT) {
		return false;
	}
	return true;
}

bool idl::OpenGLContext::loadExtFunctions(u8 colorBits, u8 depthBits) {

	if (isExtFunctionsLoaded()) {
		return true;
	}

	HWND dummy = CreateWindowExA(0, "STATIC", "", WS_OVERLAPPED, 0, 0, 0, 0, 0, 0, 0, 0);

	if (!dummy) {
		// TODO: Add Exception Manager
		MessageBoxA(NULL, "Window creation failed for dummy!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return false;
	}

	HDC dc = GetDC(dummy);

	if (!dc) {
		// TODO: Add Exception Manager
		MessageBoxA(NULL, "Recover Handle of context failed for dummy", "Error!", MB_OK | MB_ICONEXCLAMATION);
		DestroyWindow(dummy);
		return false;
	}

	PIXELFORMATDESCRIPTOR pfd = {
	    sizeof(PIXELFORMATDESCRIPTOR),  // size of this pfd
			1,                     					// version number
			PFD_DRAW_TO_WINDOW |   					// support window  
			PFD_SUPPORT_OPENGL |   					// support OpenGL  
			PFD_DOUBLEBUFFER,      					// double buffered  
			PFD_TYPE_RGBA,         					// RGBA type  
			depthBits,                  		// 24-bit color depth  
			0, 0, 0, 0, 0, 0,      					// color bits ignored  
			0,                     					// no alpha buffer  
			0,                     					// shift bit ignored  
			0,                     					// no accumulation buffer  
			0, 0, 0, 0,            					// accum bits ignored  
			colorBits,                  		// 32-bit z-buffer  
			0,                     					// no stencil buffer  
			0,                     					// no auxiliary buffer  
			PFD_MAIN_PLANE,        					// main layer
			0,                     					// reserved
			0, 0, 0                					// layer masks ignored
	};

	int pixelFormat = ChoosePixelFormat(dc, &pfd);

	if (!pixelFormat || !SetPixelFormat(dc, pixelFormat, &pfd)) {
		// TODO: Add Exception Manager
		MessageBoxA(NULL, "Setup pixel format failed for dummy", "Error!", MB_OK | MB_ICONEXCLAMATION);
		DestroyWindow(dummy);
		return false;
	}

	HGLRC rc = wglCreateContext(dc);

	if (!rc || !wglMakeCurrent(dc, rc)) {
		// TODO: Add Exception Manager
		MessageBoxA(NULL, "Context Creation failed for dummy", "Error!", MB_OK | MB_ICONEXCLAMATION);
		ReleaseDC(dummy, dc);
		DestroyWindow(dummy);
		return false;
	}

#define W(type, name) name = (type)wglGetProcAddress(#name);
	WGL_FUNCTIONS
#undef W

	wglMakeCurrent(dc, NULL);
	wglDeleteContext(rc);
	ReleaseDC(dummy, dc);
	DestroyWindow(dummy);

	if (!isExtFunctionsLoaded()) {
		// TODO: Add Exception Manager
		MessageBoxA(NULL, "OpenGL don't support WGL extensions!", "Error!", MB_OK | MB_ICONEXCLAMATION);
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
	    WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
	    WGL_SUPPORT_OPENGL_ARB,  GL_TRUE,
	    WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
	    WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
	    WGL_COLOR_BITS_ARB, color,
	    WGL_DEPTH_BITS_ARB, depth,
	    WGL_STENCIL_BITS_ARB, 8,
	    0,
	};

	const int contextAttribs[] = {
		WGL_CONTEXT_MAJOR_VERSION_ARB, major,
		WGL_CONTEXT_MINOR_VERSION_ARB, minor,
		WGL_CONTEXT_PROFILE_MASK_ARB,	WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
#if LOG_DEBUG_ENABLED
		WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_DEBUG_BIT_ARB,
#endif
		0,
	};

	memcpy(wglContextAttribs, contextAttribs, sizeof(contextAttribs));

	HWND dummy = CreateWindowExA(0, "STATIC", "", WS_OVERLAPPED, 0, 0, 0, 0, 0, 0, 0, 0);

	if (!dummy) {
		// TODO: Add Exception Manager
		MessageBoxA(NULL, "Window creation failed for dummy!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return false;
	}

	HDC dc = GetDC(dummy);

	if (!dc) {
		// TODO: Add Exception Manager
		MessageBoxA(NULL, "Recover Handle of context failed for dummy", "Error!", MB_OK | MB_ICONEXCLAMATION);
		DestroyWindow(dummy);
		return false;
	}

	u32 formats;

	if (!wglChoosePixelFormatARB(dc, pixelAttribs, 0, 1, &pixelFormat, &formats) || formats == 0) {
		// TODO: Add Exception Manager
		MessageBoxA(NULL, "OpenGL dons't support required pixel format!", "Error!", MB_OK | MB_ICONEXCLAMATION);
		DestroyWindow(dummy);
		return false;
	}

	PIXELFORMATDESCRIPTOR pfd;
	DescribePixelFormat(dc, pixelFormat, sizeof(pfd), &pfd);

	if (!pixelFormat || !SetPixelFormat(dc, pixelFormat, &pfd)) {
		// TODO: Add Exception Manager
		MessageBoxA(NULL, "Setup pixel format failed", "Error!", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}

	HGLRC rc = wglCreateContextAttribsARB(dc, NULL, wglContextAttribs);

	if (!rc || !wglMakeCurrent(dc, rc)) {
		// TODO: Add Exception Manager
		MessageBoxA(NULL, "Context Creation failed", "Error!", MB_OK | MB_ICONEXCLAMATION);
		ReleaseDC(dummy, dc);
		DestroyWindow(dummy);
		return false;
	}
	render = new RenderOpenGL();
	render->getInfo(info.renderer, info.version, info.glsl);

	initialized = true;

	wglMakeCurrent(dc, NULL);
	wglDeleteContext(rc);
	ReleaseDC(dummy, dc);
	DestroyWindow(dummy);

	return true;
}

bool idl::OpenGLContext::makeCurrent(idl_window *window) {

	if (window->context && wglMakeCurrent(window->dc, window->context))
		return true;

	IS_OPENGL_INIT

	PIXELFORMATDESCRIPTOR pfd;

	if (!pixelFormat || !SetPixelFormat(window->dc, pixelFormat, &pfd)) {
		// TODO: Add Exception Manager
		MessageBoxA(NULL, "Setup pixel format failed", "Error!", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}

	window->context = wglCreateContextAttribsARB(window->dc, NULL, wglContextAttribs);

	if (!window->context || !wglMakeCurrent(window->dc, window->context)) {
		// TODO: Add Exception Manager
		MessageBoxA(NULL, "Context Creation failed", "Error!", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}

	return true;
}

bool idl::OpenGLContext::swapInterval(idl_window* window) {
	BOOL vsync = TRUE;
	wglSwapIntervalEXT(vsync ? 1 : 0);
	return false;
}

bool idl::OpenGLContext::swapBuffers(idl_window *window) {

	IS_OPENGL_INIT
	SwapBuffers(window->dc);
	return true;
}

idl::ContextInfo idl::OpenGLContext::getInfo() {
	return info;
}

#endif