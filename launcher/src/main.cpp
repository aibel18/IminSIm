#include <EntryBase.h>
#include "render/LineRender.h"

class MyGame : public GameBase {

public:
	MyGame() {
		appConf.name = "Xsim Launcher";
		appConf.width = 1280;
		appConf.height = 720;

		// contextConf.type = idl::GraphicRenderType::IDL_OPENGL;
		contextConf.major = 3;
		contextConf.minor = 1;
	}

	std::vector<float> points = {
	    -0.0f, 0.0f, 0.0f,
			-0.5f, 0.0f, 0.0f,
			-0.5f, 1.0f, 0.0f,
			0.5f, 1.0f, 0.0f,
			0.5f, -1.0f, 0.0f,
			0.0f, -1.0f, 0.0f,
			0.0f, 0.0f, 0.0f,
	};
	LineRender *line;
	float velocity = 0.0005;
	float limit = 1.0f;

	void init() {
		line = new LineRender(points);
	}

	void update() {
		for (int i = 0; i < points.size() / 3; i++) {

			if (line->getPoint(0) > limit) {
				line->getPoint(0) = limit;
				velocity *= -1;
			}
			if (line->getPoint(0) < -limit) {
				line->getPoint(0) = -limit;
				velocity *= -1;
			}

			line->getPoint(i * 3) += velocity;
		}
		line->update();
	}

	void draw() {
		line->draw();
	}

	void end() {
		delete line;
	}

	void onResize(int width, int height) {
	}
};

MyGame myGame;