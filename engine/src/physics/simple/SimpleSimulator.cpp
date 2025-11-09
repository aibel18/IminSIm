#include "SimpleSimulator.h"
#include "util/logger.h"
#include <iostream>

xsim::SimpleSimulator::SimpleSimulator() {
}
xsim::SimpleSimulator::~SimpleSimulator() {
}

vec3 g = {0., -9.8, 0};
// float dt = 0.005f;
float eps = 0.001f;
void xsim::SimpleSimulator::step() {
  for (auto &model : models) {
    for (auto &p : model.in_particle) {
      p.p_prev = p.position;
      p.v_prev = p.velocity;
      p.velocity = p.velocity + g * dt;
      // p.velocity = p.velocity * 0.998;
      p.p_next = p.position + p.velocity * dt;
      // LOG_INFO("particle[%p] position: %f %f %f", &p, p.position.x, p.position.y, p.position.z);
    }
  }

  int iter = 0;
  // float stiffness = 0.01f;
  while (iter < 4) {
    for (auto &model : models) {
      for (auto &c : model.constraints) {
        auto &p1 = model.in_particle[c.indexA];
        auto &p2 = model.in_particle[c.indexB];

        vec3 dir = p1.p_next - p2.p_next;
        float d = norm(dir);
        vec3 n = dir / d;

        float constraint = d - c.d;

        // if( -eps < constraint && constraint < eps )
        //   continue;

        vec3 corr = -constraint * n * 0.5;

        p1.p_next = p1.p_next + corr * stiffness;
        p2.p_next = p2.p_next - corr * stiffness;

        // if (d > c.d) {
        //   std::cout << "resolution of constraints" << std::endl;
        // }
        // std::cout << c.d << std::endl;
      }
    }
    iter++;
  }

  for (auto &model : models) {
    int size = model.in_particle.size() - 1;
    // auto &pp = model.in_particle[size];
    int i = 0;
    for (auto &p : model.in_particle) {
      // float v_prev = p.velocity.y;
      p.velocity = (p.p_next - p.position) / dt;
      p.position = p.p_next;
      if (i == size)
        LOG_INFO("%i v %f <- %f p %f <- %f", i, p.velocity.y, p.v_prev.y, p.position.y, p.p_prev.y);
      i++;
      // LOG_INFO("particle[%p] position: %f %f %f", &p, p.position.x, p.position.y, p.position.z);
    }
  }

  float h = 0.6;
  // float s = 0.002;

  for (auto &model : models) {
    for (int i = 0; i < model.in_particle.size(); i++) {

      auto &p = model.in_particle[i];

      auto dist = (h + s) - p.p_next.y;

      auto diff = abs(dist) - p.r;

      if (diff >= 0) {
        continue;
      }

      p.p_prev = p.position;
      p.v_prev = p.velocity;

      // if (p.p_next.y > (h - s) && p.p_next.y < (h + s)) {
      p.p_next.y = p.p_next.y - diff;  // + 0.001f;
      // p.p_next.y = h + s - diff;  // + 0.001f;
      p.velocity = (p.p_next - p.position) / dt;
      p.position = p.p_next;
      // LOG_INFO("%i v %f <- %f p %f <- %f <<<<<< %f", i, p.velocity.y, p.v_prev.y, p.position.y, p.p_prev.y);
      LOG_INFO("%i v %f <- %f p %f <- %f <<<<<< %f", i, p.velocity.y, p.v_prev.y, p.position.y, p.p_prev.y, diff);
      // }
    }
  }
}

void xsim::SimpleSimulator::init() {
}
