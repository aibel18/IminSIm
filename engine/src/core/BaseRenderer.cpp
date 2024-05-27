#include "BaseRenderer.h"
#include "RenderRegister.h"
#include "util/logger.h"

xsim::BaseRenderer::BaseRenderer() : isLife(true), isInit(false) {
    RenderRegister::renderers.push_back(this);
    LOG_DEBUG("Created Renderer: %p", this);
}

xsim::BaseRenderer::~BaseRenderer() {
    this->isLife = false;
    LOG_DEBUG("Destroyed Renderer: %p", this);
}

// TODO: change function name
void xsim::BaseRenderer::initSuper() {
    this->init();
    this->isInit = true;
}
