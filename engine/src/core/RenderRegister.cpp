#include "RenderRegister.h"
#include "GameRegister.h"
#include "util/logger.h"

idl::Render* xsim::RenderRegister::render;
std::set<xsim::BaseRenderer*> xsim::RenderRegister::renderers;

void xsim::RenderRegister::add(BaseRenderer* renderer) {
    // TODO: how use this verification in constructor
    // if (render) {
    //     // call add function of all renderers
    //     renderer->init();
    // }

    // Game instance must be created
    if(!GameRegister::game){
        LOG_WARN("This Renderer can not be created before that a Game instance: %p", renderer);
        return;
    }
    renderers.insert(renderer);
}

void xsim::RenderRegister::remove(BaseRenderer* renderer) {
    if (renderers.erase(renderer) > 0) {
        LOG_DEBUG("Remove Renderer: %p", renderer);
    }
}

void xsim::RenderRegister::drawAll() {
    // call draw function of all renderers
    for (auto r : renderers) {
        if (!r->isInit) // TODO: how remove this flag
            r->initSuper();
        r->draw();
    }
}

void xsim::RenderRegister::cleanUp() {
    // call destructor of all Renderers that weren't destroyed
    for (auto iter = renderers.begin(); iter != renderers.end();) {
        auto temp = iter++;
        LOG_DEBUG("Free Heap Memory of Renderer before %p %i", *temp, renderers.size());
        delete (*temp);
        LOG_DEBUG("Free Heap Memory of Renderer after %p %i", *temp, renderers.size());
    }
    renderers.clear();  // TODO: verify if it's necessary this line
}
