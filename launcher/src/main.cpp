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

	u32 vao;
	u32 vbo;
	int size;
	int numPoint = 3;
	int count;

	void init() {
		float data[] = {
		    -0.5f, 0.0f,  0.0f,
		    -1.0f, -1.0f, 0.0f,
		    1.0f, -1.0f, 0.0f,
		    0.0f, 1.0f, 0.0f,
		    -1.0f, 0.0f, 0.0f,
		    0.0f, 0.0f, 0.0f
		};

		size = sizeof(data);
		count = size / (numPoint * sizeof(float));
		render->setClearColor(0.392f, 0.584f, 0.929f);
		render->initSimpleDraw(vao, vbo, data, size, numPoint, false);
	}

	void update() {
	}

	void draw() {
		render->clear();
		render->setColor(1.0f, 0.f, 0.f);
		render->drawSimple(vao, count);
	}

	void end() {
		render->endSimpleDraw(vao, vbo);
	}

	void onResize(int width, int height) {
	}
};

MyGame myGame;