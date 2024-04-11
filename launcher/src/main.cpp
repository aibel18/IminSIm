#include <EntryBase.h>
#include "core/RenderRegister.h"

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

	u32 vao;
	u32 vbo;
	int size_bytes;
	int count;
	idl::Render* render;

	float data[18] = {
			-0.5f, 0.0f,  0.0f,
			-1.0f, -1.0f, 0.0f,
			1.0f, -1.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			-1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f
	};

	float velocity[6] = {
			0.01f, 0.01f, 0.01f,
			0.01f, 0.01f, 0.01f
	};

	void init() {

		render = RenderRegister::render;

		size_bytes = sizeof(data);
		count = size_bytes / (3 * sizeof(float));
		render->setClearColor(0.392f, 0.584f, 0.929f);
		render->initData(vao, vbo, data, size_bytes, true);
	}

	void update() {
		for (int i = 0; i < 6; i++) {
			if (data[i * 3] > 1.5f) {
				data[i * 3] = 1.5f;
				velocity[i] *= -1;
			}
			if (data[i * 3] < -1.5) {
				data[i * 3] = -1.5;
				velocity[i] *= -1;
			}

			data[i * 3] += velocity[i];
		}
		render->updateData(vbo, data, size_bytes);
	}

	void draw() {
		render->clear();
		render->setColor(0.0f, 1.f, 0.f);
		render->drawData(vao, count);
	}

	void end() {
		render->endData(vao, vbo);
	}

	void onResize(int width, int height) {
	}
};

MyGame myGame;