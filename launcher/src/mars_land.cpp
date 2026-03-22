#include "mars_land.h"
#include "util/logger.h"
#include "render/LineRenderer.h"
#include "render/PointRenderer.h"

using namespace xsim;

MarsLand::MarsLand() {
  appConf.name = "Xsim Launcher";
  appConf.width = 900;
  appConf.height = 720;

  // contextConf.type = idl::GraphicRenderType::IDL_OPENGL;
  contextConf.major = 3;
  // contextConf.minor = 1;

}

std::vector<vec3> points = {{6500, 2600, 0.0f}};
 
std::vector<vec3> vertices = {
  // {0.0f, 1500.0f, 0.0f},
  // {1000.0f, 2000.0f, 0.0f},
  // {2000.0f, 500.0f, 0.0f},
  // {3500.0f, 500.0f, 0.0f},
  // {5000.0f, 1500.0f, 0.0f},
  // {6999.0f, 1000.0f, 0.0f}
  //
  // {0, 1800, 0.0f},
  // {300, 1200, 0.0f},
  // {1000, 1550, 0.0f},
  // {2000, 1200, 0.0f},
  // {2500, 1650, 0.0f},
  // {3700, 220, 0.0f},
  // {4700, 220, 0.0f},
  // {4750, 1000, 0.0f},
  // {4700, 1650, 0.0f},
  // {4000, 1700, 0.0f},
  // {3700, 1600, 0.0f},
  // {3750, 1900, 0.0f},
  // {4000, 2100, 0.0f},
  // {4900, 2050, 0.0f},
  // {5100, 1000, 0.0f},
  // {5500, 500, 0.0f},
  // {6200, 800, 0.0f},
  // {6999, 600, 0.0f}

  //
  {0, 450, 0.0f},
  {300, 750, 0.0f},
  {1000, 450, 0.0f},
  {1500, 650, 0.0f},
  {1800, 850, 0.0f},
  {2000, 1950, 0.0f},
  {2200, 1850, 0.0f},
  {2400, 2000, 0.0f},
  {3100, 1800, 0.0f},
  {3150, 1550, 0.0f},
  {2500, 1600, 0.0f},
  {2200, 1550, 0.0f},
  {2100, 750, 0.0f},
  {2200, 150, 0.0f},
  {3200, 150, 0.0f},
  {3500, 450, 0.0f},
  {4000, 950, 0.0f},
  {4500, 1450, 0.0f},
  {5000, 1550, 0.0f},
  {5500, 1500, 0.0f},
  {6000, 950, 0.0f},
  {6999, 1750, 0.0f}
 };
 	
//*/
LineRenderer* heapLine;
PointRenderer* heapPoint;
float dt = 0.1f;
vec3 g = {0,-3.711,0};
vec3 p = {0,0,0};
vec3 v = {0,0,0};

void MarsLand::init() {
  RenderRegister::render->setClearColor(0.392f, 0.584f, 0.929f);
  heapLine = new LineRenderer(vertices);
  heapPoint = new PointRenderer(points);

  p = points[0];
}

void MarsLand::update() {

  // apply gravity
  v = v + g*dt;
  p = p + v*dt;

  heapPoint->point(0) = p;
  heapPoint->update();
  
}
void MarsLand::onResize(int width, int height) {
  RenderRegister::render->setViewPort(width, height);
	// For Mars Lander Episode 3: X is 0-7000, Y is 0-3000
  RenderRegister::render->setOrtoProjection(0, 7000, 0, 3000);

  // std::cout << "resize" << std::endl;  
  LOG_INFO(">>>>> resize ");
}
