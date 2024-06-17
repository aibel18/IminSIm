#include "SimulatorBase.h"

xsim::SimulatorBase::SimulatorBase() {
}

xsim::SimulatorBase::~SimulatorBase() {
}

void xsim::SimulatorBase::addModel(Model model) {
    models.push_back(model);
}
