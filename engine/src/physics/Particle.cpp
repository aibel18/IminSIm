#include "Particle.h"
#include <iostream>

xsim::Particle::~Particle() {
  std::cout << "particle deleted" << std::endl;
}

xsim::Constraint::~Constraint() {
  std::cout << "Constraint deleted" << std::endl;
}
