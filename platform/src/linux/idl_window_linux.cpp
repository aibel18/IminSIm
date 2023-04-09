#include "idl_window_linux.h"

#if IDL_LINUX_PLATFORM

idl::idl_window* idl::create_window(const char* name, int width, int height) {

	// Connect to X
	Display* display = XOpenDisplay(NULL);

	unsigned long black, white;

	int screen = DefaultScreen(display);
	black = BlackPixel(display, screen);
	white = WhitePixel(display, screen);

	// Turn off key repeats.
	XAutoRepeatOff(display);

	Window window = XCreateSimpleWindow(
	    display, DefaultRootWindow(display), 0, 0, width, height, 0, black, white);

	if (!window) {
		return NULL;
	}

	XSetStandardProperties(display, window, name, "", None, NULL, 0, NULL);
	XSelectInput(display, window, ExposureMask | ButtonPressMask | KeyPressMask);

	// context
	GC gc = XCreateGC(display, window, 0, 0);
	if (!gc) {
		return NULL;
	}
	XSetBackground(display, gc, white);
	XSetForeground(display, gc, black);

	// custom close event
	Atom deleteMessage = XInternAtom(display, "WM_DELETE_WINDOW", False);
	XSetWMProtocols(display, window, &deleteMessage, 1);

	// clear the window and bring it on top of the other windows
	XClearWindow(display, window);
	XMapRaised(display, window);

	idl::idl_window* idlWindow = new idl::idl_window();
	idlWindow->display = display;
	idlWindow->window = window;
	idlWindow->gc = gc;
	idlWindow->deleteMessage = deleteMessage;

	return idlWindow;
}

XEvent event;    // the XEvent declaration !!!
KeySym key;      // a dealie-bob to handle KeyPress Events
char text[255];  // a char buffer for KeyPress Events

void idl::process_events(idl_window* window) {
	XNextEvent(window->display, &event);
	switch (event.type) {
		case Expose:
			if (event.xexpose.count == 0) {  // TODO: implement redraw
			}
			break;

		case KeyPress:

			XLookupString(&event.xkey, text, 255, &key, 0);  // TODO: implement input keys

			break;

		case ClientMessage:

			if (event.xclient.data.l[0] == window->deleteMessage)  // window close
				window->close = true;
			break;

		default:
			break;
	}
}

void idl::destroy_window(idl_window* idlWindow) {
	XFreeGC(idlWindow->display, idlWindow->gc);
	XDestroyWindow(idlWindow->display, idlWindow->window);
	XCloseDisplay(idlWindow->display);
}

bool idl::is_closed(idl_window* window) {
	return window->close;
}

#endif
