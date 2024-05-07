#include "BaseRenderer.h"
#include "RenderRegister.h"

xsim::BaseRenderer::BaseRenderer() {
	RenderRegister::renderers.push_back(this);
}

xsim::BaseRenderer::~BaseRenderer() {
}
