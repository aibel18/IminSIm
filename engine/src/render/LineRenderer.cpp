#include "LineRenderer.h"
#include "util/logger.h"

xsim::LineRenderer::LineRenderer(std::vector<float>& data) {
	this->data.assign(data.begin(), data.end());
	RenderRegister::render->initData(vao, vbo, &this->data[0], this->data.size() * sizeof(float), true);
}

xsim::LineRenderer::~LineRenderer() {
	RenderRegister::render->endData(vao, vbo);
	LOG_INFO("destroy");
}

float& xsim::LineRenderer::getPoint(int index) {
	return this->data[index];
}

void xsim::LineRenderer::draw() {
	RenderRegister::render->drawData(vao, data.size() / 3);
}

void xsim::LineRenderer::update() {
	RenderRegister::render->updateData(vbo, data.data(), this->data.size() * sizeof(float));
}
