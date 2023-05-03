#include <core/Application.h>

using namespace xsim;

int main() {

	ApplicationConfig config{"XSim Launcher", 1280, 720};
	Application app;
	app.create(&config);
	app.run();

	return 0;
}