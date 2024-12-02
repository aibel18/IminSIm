#include "Model.h"

void xsim::Model::addParticle(Particle particle) {
    in_particle.push_back(particle);
}

void xsim::Model::addRenderer(BaseRenderer *renderer) {
    this->renderer = renderer;
    in_particle.clear();
    for (auto v : renderer->data) {
        in_particle.push_back(Particle{.mass = 1., .position = v});
    }
}
