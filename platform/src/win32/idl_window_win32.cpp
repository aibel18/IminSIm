#include "idl_window_win32.h"

#if IDL_WINDOWS_PLATFORM

idl::idl_window *idl::create_window(const char *name, int width, int height) {

	HINSTANCE instance = GetModuleHandleA(NULL);

	// Setup and register window class.
	const char *xsimName = "XSim_Window_Class";
	WNDCLASSA windowsClass;

	if(!GetClassInfoA(instance, xsimName, &windowsClass)) {

		windowsClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		windowsClass.lpfnWndProc = process_event;
		windowsClass.cbClsExtra = 0;
		windowsClass.cbWndExtra = 0;
		windowsClass.hInstance = instance;
		windowsClass.hIcon = LoadIcon(instance, IDI_APPLICATION);
		windowsClass.hCursor = LoadCursor(NULL, IDI_APPLICATION);
		windowsClass.hbrBackground = NULL;
		windowsClass.lpszMenuName = NULL;
		windowsClass.lpszClassName = xsimName;

		if (!RegisterClassA(&windowsClass)) {
			MessageBoxA(NULL, "Window registration failed", "Error!", MB_OK | MB_ICONEXCLAMATION);
			return NULL;
		}
	}

	// Create window
	HWND handle = CreateWindowExA(
	    WS_EX_APPWINDOW,
	    xsimName,
	    name,
	    WS_OVERLAPPEDWINDOW | WS_VISIBLE,
	    CW_USEDEFAULT,
	    CW_USEDEFAULT,
	    width,
	    height,
	    NULL,
	    NULL,
	    instance,
	    NULL
	);

	if (!handle) {
		MessageBoxA(NULL, "Window creation failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return NULL;
	}

	HDC hdc = GetDC(handle);

	if (!hdc) {
		MessageBoxA(NULL, "Recover Handle of context failed", "Error!", MB_OK | MB_ICONEXCLAMATION);
		DestroyWindow(handle);
		return NULL;
	}

	idl::idl_window *window = new idl::idl_window();
	window->instance = instance;
	window->handle = handle;
	window->dc = hdc;

	return window;
}

void idl::process_events(idl_window *window) {
	MSG msg;
	while (PeekMessageA(&msg, window->handle, 0, 0, PM_REMOVE)) {

		if (msg.message == WM_QUIT) {
			window->close = true;
			return;
		}

		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}
}

void idl::destroy_window(idl_window *window) {
	if (!window)
		return;

	if (window->context) {
		wglMakeCurrent(window->dc, NULL);
		wglDeleteContext(window->context);
	}
	if (window->dc)
		ReleaseDC(window->handle, window->dc);

	if (window->handle) {
		DestroyWindow(window->handle);
		window->handle = 0;
	}
	delete window;
}

bool idl::is_closed(idl_window *window) {
	return window->close;
}

LRESULT CALLBACK idl::process_event(HWND hwnd, unsigned int msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
		case WM_CLOSE: {
			PostMessageA(hwnd, WM_QUIT, 0, 0);
			return 0;
		}
		case WM_DESTROY: {
			PostQuitMessage(0);
			return 0;
		}
	}
	return DefWindowProcA(hwnd, msg, wParam, lParam);
}

#endif
