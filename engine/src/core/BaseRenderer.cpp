#include "BaseRenderer.h"
#include "RenderRegister.h"
#include "util/logger.h"

xsim::BaseRenderer::BaseRenderer() {
    LOG_DEBUG("Created Renderer: %p", this);
    RenderRegister::add(this);
}

xsim::BaseRenderer::~BaseRenderer() {
    LOG_DEBUG("Destroyed Renderer: %p", this);
    RenderRegister::remove(this);
}