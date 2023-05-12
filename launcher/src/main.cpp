#include <EntryBase.h>

class MyGame : public GameBase {

public:
	MyGame() {
		appConf.name = "Xsim Launcher";
		appConf.width = 1280;
		appConf.height = 720;

		contextConf.type = idl::GraphicRender::IDL_OPENGL;
		contextConf.major = 3;
		contextConf.minor = 1;
	}

	void init() {
		render->setColor(0.392f, 0.584f, 0.929f);
	}

	void update() {
	}

	void draw() {
		render->clear();
		render->drawTriangle();
	}

	void onResize(int width, int height) {
	}
};

MyGame myGame;