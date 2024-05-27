#include "RenderRegister.h"
#include "util/logger.h"

idl::Render* xsim::RenderRegister::render;
std::vector<xsim::BaseRenderer*> xsim::RenderRegister::renderers;

void xsim::RenderRegister::pruning() {
    auto it = renderers.begin();
    while (it != renderers.end()) {
        if (*it && (*it)->isLife) {
            it++;
        } else {
            LOG_DEBUG("Remove Renderer: %p", (*it));
            *it = renderers.back();  // replace by the last
            renderers.pop_back();    // remove the last
        }
    }
}

void xsim::RenderRegister::add(BaseRenderer* renderer) {
    // TODO: how use this verification in constructor
    // if (render) {
    //     // call add function of all renderers
    //     renderer->init();
    // }

    renderers.push_back(renderer);
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
        if (r && r->isLife) {
            LOG_DEBUG("Free Heap Memory of Renderer %p", r);
            delete r;
            r = 0;
        }
    }
    renderers.clear();  // TODO: verify if it's necessary this line
}
