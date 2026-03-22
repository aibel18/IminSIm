#include "PointRenderer.h"
#include "util/logger.h"

xsim::PointRenderer::PointRenderer(std::vector<float>& points) : vao(0), vbo(0) {
    if (points.empty())
        return;
    this->data.resize(points.size() / 3);
    memcpy(this->data.data(), points.data(), sizeof(float) * points.size());
    LOG_DEBUG("Created PointRenderer: %p", this);
}

xsim::PointRenderer::PointRenderer(std::vector<vec3>& points) : vao(0), vbo(0) {
    this->data = points;
    LOG_DEBUG("Created PointRenderer: %p", this);
}

xsim::PointRenderer::~PointRenderer() {
    if (vao)
        RenderRegister::render->endData(vao, vbo);
}

vec3& xsim::PointRenderer::point(int index) {
    return data[index];
}

void xsim::PointRenderer::init() {
    RenderRegister::render->initData(vao, vbo, &data[0].x, data.size() * sizeof(vec3), false);
}

void xsim::PointRenderer::draw() {
    // TODO: improve how to treat alternative methods for different versions
#if IDL_WINDOWS_PLATFORM
    if (RenderRegister::render->version <= 30)
        RenderRegister::render->drawData(vao, &data[0].x, data.size());
    else
#endif
        RenderRegister::render->drawPointData(vao, data.size());
}

void xsim::PointRenderer::update() {
    RenderRegister::render->updateData(vbo, &data[0].x, data.size() * sizeof(vec3));
}
