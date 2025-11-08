#include "Model.h"
#include <iostream>

void xsim::Model::addParticle(Particle particle) {
  in_particle.push_back(particle);
}

void xsim::Model::addRenderer(BaseRenderer* renderer) {
  this->renderer = renderer;
  in_particle.clear();
  for (auto v : renderer->data) {
    in_particle.push_back(Particle{.mass = 1., .position = v});
  }
  for (int i = 0; i < in_particle.size() - 1; i += 2) {

    // Constraint* c = new Constraint();
    // Constraint c;
    // c.indexA = i;
    // c.indexB = i + 1;
    // c.d = length(in_particle[c.indexA].position, in_particle[c.indexB].position);

    constraints.push_back(Constraint{.indexA = i, .indexB = i + 1, .d = 1.f});
  }
  std::cout << ">>>> " << constraints.size() << std::endl;
}

xsim::Model::~Model() {
  // for (int i = 0; i < constraints.size(); i++) {
  //   delete constraints[i];
  // }
  std::cout << "model deleted" << std::endl;
}
