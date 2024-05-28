#include "RenderRegister.h"
#include "GameRegister.h"
#include "util/logger.h"

idl::Render* xsim::RenderRegister::render;
std::vector<xsim::BaseRenderer*> xsim::RenderRegister::renderers;

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
    renderers.push_back(renderer);
}

void xsim::RenderRegister::remove(BaseRenderer* renderer) {
    auto it = renderers.begin();
    // TODO: find element to constant complexity
    while (it != renderers.end()) {
        if (*it == renderer) {
            LOG_DEBUG("Remove Renderer: %p", (*it));
        
            *it = renderers.back();  // replace by the last
            renderers.pop_back();    // remove the last
            return;
        }
        it++;
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
    for (auto r : renderers) {
        LOG_DEBUG("Free Heap Memory of Renderer %p", r);
        delete r;
        r = 0;
    }
    renderers.clear();  // TODO: verify if it's necessary this line
}
