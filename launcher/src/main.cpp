#include <EntryBase.h>
#include "render/LineRenderer.h"
#include "math/math_defines.h"

class MyGame : public BaseGame {

public:
	MyGame() {
		appConf.name = "Xsim Launcher";
		appConf.width = 1280;
		appConf.height = 720;

		// contextConf.type = idl::GraphicRenderType::IDL_OPENGL;
		contextConf.major = 3;
		contextConf.minor = 1;
	}

	std::vector<vec3> points = {
	    {-0.0f, 0.0f, 0.0f},
		{-0.5f, 0.0f, 0.0f},
		{-0.5f, 1.0f, 0.0f},
		{0.5f, 1.0f, 0.0f},
		{0.5f, -1.0f, 0.0f},
		{0.0f, -1.0f, 0.0f},
		{0.0f, 0.0f, 0.0f}
	};

	float velocity = 0.0009;
	float limit = 1.0f;
	LineRenderer line = LineRenderer(points);;
	LineRenderer *line2 = new LineRenderer(points);
	LineRenderer *line3;
	LineRenderer *line4;
	LineRenderer *line5;

	void init() {
        line5 = new LineRenderer(points);
        LineRenderer line6 = LineRenderer(points);
	}

    int i = 0;
    int step = 300;
	void update() {
        if(i++ == step ) {
            delete line2;
            delete line5;
            LineRenderer line6 = LineRenderer(points);
        }
        if(i == step *2 ) {
            line3 = new LineRenderer(points);
        }
        if(i == step *3 ) {
            delete line3;
        }
        if(i == step *4 ) {
            LineRenderer a(points);
            LineRenderer b(points);
            line4 = new LineRenderer(points);
        }
        if(i == step *5 ) {
            new LineRenderer(points);
        }

        if(i > step *5)
            return;

		for (int i = 0; i < points.size(); i++) {

			if (line.getPoint(0).x > limit) {
				line.getPoint(0).x = limit;
				velocity *= -1;
			}
			if (line.getPoint(0).x < -limit) {
				line.getPoint(0).x = -limit;
				velocity *= -1;
			}

			line.getPoint(i).x += velocity;
		}
		line.update();
	}

	void end() {
        delete line4;
	}

	void onResize(int width, int height) {
	}
};

BaseGame* createGame() {
    return new MyGame;
}