#include "SimpleSimulator.h"
#include "util/logger.h"
#include <iostream>

xsim::SimpleSimulator::SimpleSimulator() {
}
xsim::SimpleSimulator::~SimpleSimulator() {
}

vec3 g = {0., -9.8, 0};
float dt = 0.001f;
void xsim::SimpleSimulator::step() {
  for (auto &model : models) {
    for (auto &p : model.in_particle) {
      p.velocity = p.velocity + g * dt;
      p.p_next = p.position + p.velocity * dt;
      // LOG_INFO("particle[%p] position: %f %f %f", &p, p.position.x, p.position.y, p.position.z);
    }
  }

  int iter = 0;
  // while (iter < 4) {
    for (auto &model : models) {
      // for (auto &c : model.constraints) {
        // c.d;
        // auto p1 = model.in_particle[c.indexA];
        // auto p2 = model.in_particle[c.indexB];

        // float d = length(p1.position, p2.position);

        // if (d < c.d) {
        //   std::cout << "resolution of constraints" << std::endl;
        // }
        // std::cout << c.d << std::endl;
      // }s
    }
  //   iter++;
  // }

  for (auto &model : models) {
    for (auto &p : model.in_particle) {
      p.velocity = (p.p_next - p.position) / dt;
      p.position = p.p_next;
      // LOG_INFO("particle[%p] position: %f %f %f", &p, p.position.x, p.position.y, p.position.z);
    }
  }
}

void xsim::SimpleSimulator::init() {
}
