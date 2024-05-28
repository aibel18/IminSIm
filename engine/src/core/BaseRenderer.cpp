#include "BaseRenderer.h"
#include "RenderRegister.h"
#include "util/logger.h"

xsim::BaseRenderer::BaseRenderer() : isInit(false) {
    LOG_DEBUG("Created Renderer: %p", this);
    RenderRegister::add(this);
}

xsim::BaseRenderer::~BaseRenderer() {
    LOG_DEBUG("Destroyed Renderer: %p", this);
    RenderRegister::remove(this);
}

// TODO: change function name
void xsim::BaseRenderer::initSuper() {
    this->init();
    this->isInit = true;
}
