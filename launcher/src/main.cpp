#include <EntryBase.h>
#include "render/LineRenderer.h"
#include "math/math_defines.h"
#include "core/SimulatorRegister.h" // TODO: improve call to headers
#include "physics/SimulatorFactory.h"
#include "physics/Particle.h"

class MyGame : public BaseGame {

public:
	MyGame() {
		appConf.name = "Xsim Launcher";
		appConf.width = 1280;
		appConf.height = 720;

		// contextConf.type = idl::GraphicRenderType::IDL_OPENGL;
		contextConf.major = 2;
		contextConf.minor = 1;
        
        SimulatorFactory::createInstance();
	}

 std::vector<vec3> points = {
  {0.0f, -0.2f, 0.0f},
  {0.0f, 0.1f, 0.0f},
  {0.0f, 0.4f, 0.0f},
  {0.0f, 0.74f, 0.0f},
  {0.0f, 1.0f, 0.0f}
 };
 
 std::vector<vec3> vertices = {
  {-0.1f, -0.2f, 0.0f},
  {-0.1f, -0.05f, 0.0f},
  {-0.1f, 0.1f, 0.0f},
  {-0.1f, 0.5f, 0.0f},
  {-0.1f, 1.0f, 0.0f},
  {-0.1f, 1.2f, 0.0f},
  {0.1f, 1.2f, 0.0f},
  {0.1f, 1.0f, 0.0f},
  {0.1f, 0.5f, 0.0f},
  {0.1f, 0.1f, 0.0f},
  {0.1f, -0.05f, 0.0f},
  {0.1f, -0.2f, 0.0f}
 };
 
 std::vector<std::vector<float>> weigths;
 std::vector<std::vector<int>> weigthsIds;
 std::vector<std::vector<vec3>> distances;

	float velocity = 0.0009;
	float limit = 1.0f;
	LineRenderer stackLine = LineRenderer(points);
	LineRenderer stackLine2 = LineRenderer(vertices);
	
	int modelId = -1;

	void init() {
        RenderRegister::render->setClearColor(0.392f, 0.584f, 0.929f);
        // heapLine = new LineRenderer(points);

        Model model;
        model.addRenderer(&stackLine);

        SimulatorRegister::simulator->stiffness = 0.01f;
        // SimulatorRegister::simulator->s = ;
        SimulatorRegister::simulator->h = 0.75;
        SimulatorRegister::simulator->dt = 0.005f;

        modelId = SimulatorRegister::simulator->addModel(model); // TODO: add a model automatically
        
        float dis = 0.3f;
        
        for(int i = 0; i < vertices.size(); i++) {
          float sum = 0.f;
          weigths.push_back(std::vector<float>());
          weigthsIds.push_back(std::vector<int>());
          distances.push_back(std::vector<vec3>());
          for(int j = 0; j < points.size(); j++) {
            auto d = vertices[i] - points[j];
            float l = norm(d);
            if( l < dis) {
              sum += 1.0 / (l * l);
              weigths[i].push_back(1.0 / (l * l));
              weigthsIds[i].push_back(j);
              distances[i].push_back(d);
            }
          }
          for(int k = 0; k < weigthsIds[i].size(); k++) {
            weigths[i][k] = weigths[i][k] / sum;
            LOG_INFO("%i -> (%f %f %f) %f", weigthsIds[i][k], distances[i][k].x, distances[i][k].y, distances[i][k].z, weigths[i][k]);
          }
          LOG_INFO(">>>>>%f", sum);
        }

        // LOG_INFO("Model added %p", &model);
        
        auto& m = SimulatorRegister::simulator->models[modelId];
        auto& p_last = m.in_particle[points.size() -1];
        p_last.position.x += 0.02f; // add force in x
        p_last.position.z += 0.01f; // add force in z
    }
    

    int iter = 0;
	void update() {
	
    auto& m = SimulatorRegister::simulator->models[modelId];
    // int size = m.in_particle.size();
    // for (int i = 0; i < size ; i++) {
    //   auto pos = m.in_particle[i].position;
    //   stackLine2.point(i).y = pos.y;
    // }
    auto size = stackLine2.pointSize();
    for (int i = 0; i < size; i++) {
      vec3 totMove = {0,0,0};
      for (int k = 0; k < weigths[i].size(); k++) {
        totMove = totMove + weigths[i][k] * ( m.in_particle[weigthsIds[i][k]].position + distances[i][k]);
      }
      stackLine2.point(i) = totMove;
    }
    stackLine2.update();

        // if (iter % 400 == 0) {
        //     if (heapLine == 0) {
        //         heapLine = new LineRenderer(points);
        //     } else {
        //         delete heapLine;
        //         heapLine = 0;
        //     }
        // }
        // iter++;
        // auto size = stackLine.pointSize();
        // for (int i = 0; i < size; i++) {

        //     if (stackLine.point(0).x > limit) {
		// 		stackLine.point(0).x = limit;
		// 		velocity *= -1;
		// 	}
		// 	if (stackLine.point(0).x < -limit) {
		// 		stackLine.point(0).x = -limit;
		// 		velocity *= -1;
			}

		// 	stackLine.point(i).x += velocity;
        // }
        // stackLine.update();
        // heapLine->update();
	// }

	void end() {
	}

	void onResize(int width, int height) {
	}
};

BaseGame* createGame() {
    return new MyGame;
}
