#include "SimulatorBase.h"
#include "util/logger.h"

xsim::SimulatorBase::SimulatorBase() {
}

xsim::SimulatorBase::~SimulatorBase() {
}

int xsim::SimulatorBase::addModel(Model& model) {
  int id = models.size();
  models.push_back(model);
  return id;
}

void xsim::SimulatorBase::updateOutPosition() {
    for (auto &model : models) {
        int size = model.in_particle.size();
        for (auto i = 0; i < size ;i++) {
            model.renderer->data[i] = model.in_particle[i].position;
        }
        model.renderer->update();
    }
}
