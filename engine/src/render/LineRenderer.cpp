#include "LineRenderer.h"
#include "util/logger.h"

xsim::LineRenderer::LineRenderer(std::vector<float>& points) : vao(0), vbo(0) {
    if (points.empty())
        return;
    this->data.resize(points.size() / 3);
    memcpy(this->data.data(), points.data(), sizeof(float) * points.size());
}

xsim::LineRenderer::LineRenderer(std::vector<vec3>& points) : vao(0), vbo(0) {
    this->data = points;
}

xsim::LineRenderer::~LineRenderer() {
    if (vao)
        RenderRegister::render->endData(vao, vbo);
}

vec3& xsim::LineRenderer::getPoint(int index) {
    return data[index];
}

void xsim::LineRenderer::init() {
    RenderRegister::render->initData(vao, vbo, &data[0].x, data.size() * sizeof(vec3), false);
}

void xsim::LineRenderer::draw() {
    RenderRegister::render->drawData(vao, data.size());
}

void xsim::LineRenderer::update() {
    RenderRegister::render->updateData(vbo, &data[0].x, data.size() * sizeof(vec3));
}
