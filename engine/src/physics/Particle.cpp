#include "Particle.h"
#include <iostream>

// xsim::Particle::Particle() {
//   std::cout << "particle created " << this << std::endl;
// }

xsim::Particle::~Particle() {
  std::cout << "particle deleted " << this << std::endl;
}

// xsim::Constraint::Constraint() {
//   std::cout << "Constraint created " << this << std::endl;
// }

xsim::Constraint::~Constraint() {
  std::cout << "Constraint deleted " << this << std::endl;
}
