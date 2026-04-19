#ifndef DEMOS_SPRING_SIMULATION_H
#define DEMOS_SPRING_SIMULATION_H

#include "core/BaseGame.h"
#include "render/LineRenderer.h"
class SpringSimulation : public xsim::BaseGame {

public:
  SpringSimulation();

  void init() override;
  void update() override;

  std::vector<vec3> points = {
      {0.0f, -0.2f, 0.0f},
      {0.0f,  0.1f, 0.0f},
      {0.0f,  0.4f, 0.0f},
      {0.0f, 0.74f, 0.0f},
      {0.0f,  1.0f, 0.0f}
  };
  std::vector<vec3> vertices = {
      {-0.1f,  -0.2f, 0.0f},
      {-0.1f, -0.05f, 0.0f},
      {-0.1f,   0.1f, 0.0f},
      {-0.1f,   0.5f, 0.0f},
      {-0.1f,   1.0f, 0.0f},
      {-0.1f,   1.2f, 0.0f},
      { 0.1f,   1.2f, 0.0f},
      { 0.1f,   1.0f, 0.0f},
      { 0.1f,   0.5f, 0.0f},
      { 0.1f,   0.1f, 0.0f},
      { 0.1f, -0.05f, 0.0f},
      { 0.1f,  -0.2f, 0.0f}
  };
  xsim::LineRenderer stackLine = xsim::LineRenderer(points);
  xsim::LineRenderer stackLine2 = xsim::LineRenderer(vertices);
};

#endif
