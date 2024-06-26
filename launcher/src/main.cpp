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
	LineRenderer stackLine = LineRenderer(points);
	LineRenderer *heapLine;

	void init() {
        heapLine = new LineRenderer(points);
	}

    int iter = 0;
	void update() {

        if (iter % 400 == 0) {
            if (heapLine == 0) {
                heapLine = new LineRenderer(points);
            } else {
                delete heapLine;
                heapLine = 0;
            }
        }
        iter++;
        auto size = stackLine.pointSize();
        for (int i = 0; i < size; i++) {

            if (stackLine.point(0).x > limit) {
				stackLine.point(0).x = limit;
				velocity *= -1;
			}
			if (stackLine.point(0).x < -limit) {
				stackLine.point(0).x = -limit;
				velocity *= -1;
			}

			stackLine.point(i).x += velocity;
        }
        stackLine.update();
	}

	void end() {
	}

	void onResize(int width, int height) {
	}
};

BaseGame* createGame() {
    return new MyGame;
}