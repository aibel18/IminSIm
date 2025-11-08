#include "RenderRegister.h"
#include "GameRegister.h"
#include "util/logger.h"

idl::Render* xsim::RenderRegister::render;
std::unordered_set<xsim::BaseRenderer*> xsim::RenderRegister::renderers;
std::unordered_set<xsim::BaseRenderer*> xsim::RenderRegister::no_init_renderers;

void xsim::RenderRegister::add(BaseRenderer* renderer) {

    // Game instance must be created
    if(!GameRegister::game){
        LOG_WARN("This Renderer can not be created before that a Game instance: %p", renderer);
        return;
    }
    renderers.insert(renderer);
    no_init_renderers.insert(renderer);
    LOG_DEBUG("Add Renderer: %p", renderer);
}

void xsim::RenderRegister::remove(BaseRenderer* renderer) {
    if (renderers.erase(renderer) > 0) {
        LOG_DEBUG("Remove Renderer: %p", renderer);
        if (no_init_renderers.erase(renderer) > 0) {
            LOG_DEBUG("Remove Renderer: %p of no_init_renderers", renderer);
        }
    }
}

void xsim::RenderRegister::initAll() {
    // call init function of all renderers one time
    for (auto iter = no_init_renderers.begin(); iter != no_init_renderers.end();) {
        auto renderer = (*iter++);
        renderer->init();
        if (no_init_renderers.erase(renderer) > 0) {
            LOG_DEBUG("Remove Renderer: %p of no_init_renderers", renderer);
        }
    }
}
void xsim::RenderRegister::drawAll() {
    
	RenderRegister::render->clear();

    // call draw function of all renderers
    for (auto renderer : renderers) {
        renderer->draw();
    }
}

void xsim::RenderRegister::cleanUp() {
    // call destructor of all Renderers that weren't destroyed
    for (auto iter = renderers.begin(); iter != renderers.end();) {
        auto renderer = (*iter++);
        LOG_DEBUG("Free Heap Memory of Renderer before %p %i", renderer, renderers.size());
        delete renderer;
        LOG_DEBUG("Free Heap Memory of Renderer after %p %i", renderer, renderers.size());
    }
    renderers.clear();  // TODO: verify if it's necessary this line
    no_init_renderers.clear();  // TODO: verify if it's necessary this line
}
