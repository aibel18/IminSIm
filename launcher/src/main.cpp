#include <EntryBase.h>

using namespace xsim;

class MyGame : public GameBase {
public:
	MyGame() {
		config.name = "Xsim Launcher";
		config.width = 1280;
		config.height = 720;
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

GameBase* CreateGame() {
	return &myGame;
}

void DestroyGame(GameBase* game) {
	// delete game;
}