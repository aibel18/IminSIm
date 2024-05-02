#include "LineRender.h"
#include "util/logger.h"

xsim::LineRender::LineRender(std::vector<float>& data) {
	this->data.assign(data.begin(), data.end());
	RenderRegister::render->initData(vao, vbo, &this->data[0], this->data.size() * sizeof(float), true);
}

xsim::LineRender::~LineRender() {
	RenderRegister::render->endData(vao, vbo);
	LOG_INFO("destroy");
}

float& xsim::LineRender::getPoint(int index) {
	return this->data[index];
}

void xsim::LineRender::draw() {
	RenderRegister::render->drawData(vao, data.size() / 3);
}

void xsim::LineRender::update() {
	RenderRegister::render->updateData(vbo, data.data(), this->data.size() * sizeof(float));
}
