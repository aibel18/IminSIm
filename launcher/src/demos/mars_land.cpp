#include "mars_land.h"
#include "util/logger.h"
#include "render/LineRenderer.h"
#include "render/PointRenderer.h"

#include "mars_land_solver.h"

using namespace xsim;

MarsLand::MarsLand() {
  appConf.name = "Mars Land";
  appConf.width = 900;
  appConf.height = 720;

  contextConf.major = 3;
}

std::vector<vec3> rocket = {
    {  0, 40, 0},
    { 40,  0, 0},
    { 40,-40, 0},
    {  0,  0, 0},
    {-40,-40, 0},
    {-40,  0, 0},
    {  0, 40, 0},
};

std::vector<vec3> land1 = {
    {   0, 1800, 0.0f},
    { 300, 1200, 0.0f},
    {1000, 1550, 0.0f},
    {2000, 1200, 0.0f},
    {2500, 1650, 0.0f},
    {3700,  220, 0.0f},
    {4700,  220, 0.0f},
    {4750, 1000, 0.0f},
    {4700, 1650, 0.0f},
    {4000, 1700, 0.0f},
    {3700, 1600, 0.0f},
    {3750, 1900, 0.0f},
    {4000, 2100, 0.0f},
    {4900, 2050, 0.0f},
    {5100, 1000, 0.0f},
    {5500,  500, 0.0f},
    {6200,  800, 0.0f},
    {6999,  600, 0.0f}
};
std::vector<vec3> land2 = {
    {   0,  450, 0.0f},
    { 300,  750, 0.0f},
    {1000,  450, 0.0f},
    {1500,  650, 0.0f},
    {1800,  850, 0.0f},
    {2000, 1950, 0.0f},
    {2200, 1850, 0.0f},
    {2400, 2000, 0.0f},
    {3100, 1800, 0.0f},
    {3150, 1550, 0.0f},
    {2500, 1600, 0.0f},
    {2200, 1550, 0.0f},
    {2100,  750, 0.0f},
    {2200,  150, 0.0f},
    {3200,  150, 0.0f},
    {3500,  450, 0.0f},
    {4000,  950, 0.0f},
    {4500, 1450, 0.0f},
    {5000, 1550, 0.0f},
    {5500, 1500, 0.0f},
    {6000,  950, 0.0f},
    {6999, 1750, 0.0f}
};

std::vector<vec3> land3 = {
    {   0,  1000, 0.0f},
    { 300,  2500, 0.0f},
    {1000,  2500, 0.0f},
    {1500,  2000, 0.0f},
    {1800,  850, 0.0f},
    {2000, 1950, 0.0f},
    {2200, 1850, 0.0f},
    {2400, 2000, 0.0f},
    {3100, 1800, 0.0f},
    {3150, 1550, 0.0f},
    {2500, 1600, 0.0f},
    {2200, 1550, 0.0f},
    {2100,  900, 0.0f},
    {2200,  1050, 0.0f},
    {3200,  150, 0.0f},
    {3500,  450, 0.0f},
    {4000,  950, 0.0f},
    {4500, 1450, 0.0f},
    {5000, 1550, 0.0f},
    {5500, 1500, 0.0f},
    {6000,  950, 0.0f},
    {6999, 1750, 0.0f}
};

LineRenderer* heapLine;
LineRenderer* heapPoint;

float dt = 0.1f;
vec3 g = {0, -3.711, 0};
vec3 p = {0, 0, 0};
vec3 v = {0, 0, 0};

void MarsLand::init() {
  RenderRegister::render->setClearColor(0.392f, 0.584f, 0.929f);
  heapLine = new LineRenderer(land1);
  heapPoint = new LineRenderer(rocket);

  p = {6500, 2200, 0.0f};// init position
  v = {20, -5}; // init velocity
  findGoal(heapLine->data);
}

void MarsLand::update() {
  int angle, power;
  solve(p, v, g, angle, power);

  // apply physics
  auto acc = acceleration(angle, power, g);
  v = v + acc * dt;
  p = p + v * dt;

  if( verifySolution(p, v, angle) ) {
    LOG_INFO(">>>>> Congrats!!");
    return;
  }

  float angleRadians = angle * fact_to_radiam;
  float s = sin(angleRadians);
  float c = cos(angleRadians);

  for(int i = 0; i < heapPoint->data.size(); i ++ ){
    float xnew = rocket[i].x * c - rocket[i].y * s + p.x;
    float ynew = rocket[i].x * s + rocket[i].y * c + p.y;
    heapPoint->point(i) = {xnew, ynew, 0};
  }
  // heapPoint->point(0) = vec3{p.x, p.y, 0};
  heapPoint->update();
}
void MarsLand::onResize(int width, int height) {
  RenderRegister::render->setViewPort(width, height);
  // For Mars Lander Episode 3: X is 0-7000, Y is 0-3000
  RenderRegister::render->setOrtoProjection(0, 7000, 0, 3000);

  LOG_INFO(">>>>> resize ");
}
