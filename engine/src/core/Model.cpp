#include "Model.h"
#include <iostream>

void xsim::Model::addParticle(Particle particle) {
  in_particle.push_back(particle);
  std::cout << "added " << &particle << std::endl;
}

void xsim::Model::addRenderer(BaseRenderer* renderer) {
  this->renderer = renderer;
  in_particle.clear();
  in_particle.reserve(renderer->data.size());
  int i = 0;
  for (auto v : renderer->data) {
    std::cout << "particle " << i << std::endl;
    in_particle.push_back(Particle{.mass = (1.f * i), .position = v});
    i++;
  }
  std::cout << ">>>> " << in_particle.size() << std::endl;
  constraints.clear();
  constraints.reserve(renderer->data.size() - 1);
  for (int i = 0; i < in_particle.size() - 1; i++) {

    // Constraint* c = new Constraint();
    // Constraint c;
    // c.indexA = i;
    // c.indexB = i + 1;
    float d = length(in_particle[i].position, in_particle[i+1].position);
    constraints.push_back(Constraint{.indexA = i, .indexB = i + 1, .d = d});
  }
  std::cout << ">>>> " << constraints.size() << std::endl;
  std::cout << ">>>> <<<<<<<<< " << std::endl;
}

xsim::Model::~Model() {
  // for (int i = 0; i < constraints.size(); i++) {
  //   delete constraints[i];
  // }
  std::cout << "model deleted " << this << std::endl;
}
